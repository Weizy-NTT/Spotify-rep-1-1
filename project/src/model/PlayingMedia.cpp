#include "PlayingMedia.hpp"
#include <iostream>

// A simple audio packet queue
std::queue<AVPacket*> audioQueue;
std::mutex audioQueueMutex;

// Audio settings
int64_t audio_out_channel_layout = AV_CH_LAYOUT_STEREO;
int audio_out_channels = av_get_channel_layout_nb_channels(audio_out_channel_layout);
int audio_out_sample_rate = 44100;
AVSampleFormat audio_out_sample_fmt = AV_SAMPLE_FMT_S16;

std::shared_ptr<MediaFile> PlayingMedia::getCurrentMediaFile() const {
    if (currentplaylist.empty() || currentTrackIndex < 0 || currentTrackIndex >= currentplaylist.size()){
        return nullptr;
    } 
    return currentplaylist[currentTrackIndex];
}

void PlayingMedia::setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile) {
    if (!mediaFile) {
        std::cerr << "Error: Invalid media file." << std::endl;
        return;
    }
    if (!getCurrentMediaFile() || (mediaFile->getID() != getCurrentMediaFile()->getID())) {
        for (size_t i = 0; i < currentplaylist.size(); ++i) {
            if (currentplaylist[i]->getID() == mediaFile->getID()) {
                stop();
                {
                    std::unique_lock<std::recursive_mutex> lock(stateMutex);
                    currentTrackIndex = i;
                }
                play();
                return;
            }
        }
    }
}

void PlayingMedia::setPlaylist(const std::vector<std::shared_ptr<MediaFile>>& newPlaylist) 
{
    if (newPlaylist != currentplaylist) {
        stop();
        std::unique_lock<std::recursive_mutex> lock(stateMutex);
        currentplaylist = newPlaylist;
    }
}

size_t PlayingMedia::getCurrentTime() const {
    return currentTime;
}

size_t PlayingMedia::getTotalTime() const {
    return totalTime;
}  

void PlayingMedia::setCurrentTime(size_t time) {
    currentTime = time;
}

PlayingMedia::PlayingMedia() : volume(50) {
    Mix_VolumeMusic(volume);
}

PlayingMedia::~PlayingMedia(){
    stopPlaybackThread();
}

void PlayingMedia::playAudio(const char* filePath) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw std::runtime_error("Failed to initialize SDL_mixer: " + std::string(Mix_GetError()));
    }

    Mix_Music* music = Mix_LoadMUS(filePath);
    if (!music) {
        Mix_CloseAudio();
        throw std::runtime_error("Failed to load audio file: " + std::string(Mix_GetError()));
    }

    playing = true;
    Mix_PlayMusic(music, 1);

    while (Mix_PlayingMusic()) {
        {
            std::unique_lock<std::recursive_mutex> lock(stateMutex);
            Mix_VolumeMusic(volume);
            if (!playing) {
                Mix_HaltMusic();
                break;
            }
            if (paused) {
                Mix_PauseMusic();
                while (paused && playing) {
                    lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    lock.lock();
                }
                Mix_ResumeMusic();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
}

void PlayingMedia::play() {
    if (currentplaylist.empty()) {
        return;
    }

    stopPlaybackThread(); // Stop any existing playback thread
    {
        std::unique_lock<std::recursive_mutex> lock(stateMutex);
        currentTime = 0;
        totalTime = currentplaylist[currentTrackIndex]->getDuration();
    }
    playbackThread = std::thread(&PlayingMedia::playCurrentTrack, this);
}

void PlayingMedia::pauseMusic() {
    std::unique_lock<std::recursive_mutex> lock(stateMutex);
    if (!playing || paused) {
        return;
    }
    paused = true;
    Mix_PauseMusic();
}

void PlayingMedia::resumeMusic() {
    std::unique_lock<std::recursive_mutex> lock(stateMutex);
    if (!playing || !paused) {
        return;
    }
    paused = false;
    Mix_ResumeMusic();
}

void PlayingMedia::stop(){  
    stopPlaybackThread();
}

bool PlayingMedia::isPlaying() {
    return Mix_PlayingMusic();
}

void PlayingMedia::adjustVolume(size_t newVolume){
    volume = newVolume;
    Mix_VolumeMusic(volume);
}

void PlayingMedia::stopPlaybackThread() {
    if (playbackThread.joinable()) {
        {
            std::unique_lock<std::recursive_mutex> lock(stateMutex);
            playing = false;
        }
        playbackThread.join();
    }
}

void PlayingMedia::playCurrentTrack(){
    {
        std::unique_lock<std::recursive_mutex> lock(stateMutex);
        playing = true;
        paused = false;
    }
    if(!currentplaylist.empty()){
        std::string currentTrackPath = currentplaylist[currentTrackIndex]->getPath();
        if (currentplaylist[currentTrackIndex]->getType() == MediaType::AUDIO) {
            playAudio(currentTrackPath.c_str());
        }
        else {
            std::string wavpath = extractAudio(currentTrackPath);
            playVideo(currentTrackPath.c_str(),wavpath.c_str());
        }
    } else {
        std::cerr <<"No tracks available to play.\n";
    }

    {
        std::unique_lock<std::recursive_mutex> lock(stateMutex);
        playing = false;
    }
}

void PlayingMedia::nextTrack() {
    stop();
    {
        std::unique_lock<std::recursive_mutex> lock(stateMutex);
        currentTrackIndex = (currentTrackIndex + 1) % currentplaylist.size();
    }
    play();
}

void PlayingMedia::previousTrack() {
    stop();
    {
        std::unique_lock<std::recursive_mutex> lock(stateMutex);
        currentTrackIndex = (currentTrackIndex == 0) ? currentplaylist.size() - 1 : currentTrackIndex - 1;
    }
    play();
}

bool PlayingMedia::hasNextTrack() const {
    return currentTrackIndex >= 0 && currentTrackIndex < currentplaylist.size() - 1;
}

bool PlayingMedia::hasPrevTrack() const {
    return currentTrackIndex > 0 && currentTrackIndex < currentplaylist.size();
}

std::string PlayingMedia::extractAudio(const std::string &videoPath) {
    std::string outputFolderPath = "./resources/musicfrommp4";
    std::string outputAudioPath = outputFolderPath + "/" + fs::path(videoPath).stem().string() + ".wav";
    std::string command = "ffmpeg -i \"" + videoPath + "\" -q:a 0 -map a \"" + outputAudioPath + "\" -y";

    if(!fs::exists(outputFolderPath)){
        fs::create_directories(outputFolderPath);
    }

    if (fs::exists(outputAudioPath)) {
        return outputAudioPath;
    }
    
    int result = system(command.c_str());
    if(result != 0){
        std::cerr << "Failed to extract audio using FFmpeg.\n";
        return "";
    }

    std::cout <<  "Audio extracted to: " << outputAudioPath << "\n";
    return outputAudioPath;
} 

void PlayingMedia::playVideo(const char* videoFilePath, const char* wavPath) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
        SDL_Quit();
        return;
    }

    // Load the music
    Mix_Music* music = Mix_LoadMUS(wavPath);
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << "\n";
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    // Play the music
    if (Mix_PlayMusic(music, -1) == -1) { // -1: loop indefinitely
        std::cerr << "Failed to play music: " << Mix_GetError() << "\n";
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    // Video playback logic
    avformat_network_init();
    AVFormatContext* formatContext = nullptr;

    if (avformat_open_input(&formatContext, videoFilePath, nullptr, nullptr) != 0) {
        std::cerr << "Failed to open video file: " << videoFilePath << "\n";
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        avformat_close_input(&formatContext);
        std::cerr << "Failed to retrieve stream info.\n";
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    int videoStreamIndex = -1;
    for (unsigned i = 0; i < formatContext->nb_streams; ++i) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && videoStreamIndex == -1) {
            videoStreamIndex = i;
        }
    }

    if (videoStreamIndex == -1) {
        avformat_close_input(&formatContext);
        std::cerr << "No video stream found.\n";
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    AVCodecParameters* videoCodecParams = formatContext->streams[videoStreamIndex]->codecpar;
    AVCodec* videoCodec = avcodec_find_decoder(videoCodecParams->codec_id);
    if (!videoCodec) {
        avformat_close_input(&formatContext);
        std::cerr << "Unsupported video codec.\n";
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    AVCodecContext* videoCodecContext = avcodec_alloc_context3(videoCodec);
    avcodec_parameters_to_context(videoCodecContext, videoCodecParams);
    if (avcodec_open2(videoCodecContext, videoCodec, nullptr) < 0) {
        avcodec_free_context(&videoCodecContext);
        avformat_close_input(&formatContext);
        std::cerr << "Failed to open video codec.\n";
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    SDL_Window* window = SDL_CreateWindow("Video Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          videoCodecContext->width, videoCodecContext->height, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
                                             videoCodecContext->width, videoCodecContext->height);

    SwsContext* swsContext = sws_getContext(videoCodecContext->width, videoCodecContext->height, videoCodecContext->pix_fmt,
                                            videoCodecContext->width, videoCodecContext->height, AV_PIX_FMT_YUV420P,
                                            SWS_BILINEAR, nullptr, nullptr, nullptr);

    AVFrame* frame = av_frame_alloc();
    AVFrame* frameYUV = av_frame_alloc();
    int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, videoCodecContext->width, videoCodecContext->height, 1);
    uint8_t* buffer = (uint8_t*)av_malloc(bufferSize);
    av_image_fill_arrays(frameYUV->data, frameYUV->linesize, buffer, AV_PIX_FMT_YUV420P,
                         videoCodecContext->width, videoCodecContext->height, 1);

    AVPacket packet;
    bool quit = false;

    // Calculate frame delay
    double frameDelay = 40.0; // Default for ~25 FPS
    if (formatContext->streams[videoStreamIndex]->avg_frame_rate.num > 0) {
        double fps = av_q2d(formatContext->streams[videoStreamIndex]->avg_frame_rate);
        frameDelay = 1000.0 / fps; // Convert to milliseconds
    }

    while (av_read_frame(formatContext, &packet) >= 0 && !quit) {
        if (packet.stream_index == videoStreamIndex) {
            if (avcodec_send_packet(videoCodecContext, &packet) == 0) {
                while (avcodec_receive_frame(videoCodecContext, frame) == 0) {
                    sws_scale(swsContext, frame->data, frame->linesize, 0, videoCodecContext->height,
                              frameYUV->data, frameYUV->linesize);

                    SDL_UpdateYUVTexture(texture, nullptr,
                                         frameYUV->data[0], frameYUV->linesize[0],
                                         frameYUV->data[1], frameYUV->linesize[1],
                                         frameYUV->data[2], frameYUV->linesize[2]);

                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
                    SDL_RenderPresent(renderer);

                    // Delay to control frame rate
                    //SDL_Delay(static_cast<int>(frameDelay));
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(frameDelay)));

                    // Handle SDL events and playback state
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            quit = true;
                        }
                    }

                    // Check `paused` and `playing` state
                    {
                        std::unique_lock<std::recursive_mutex> lock(stateMutex);
                        Mix_VolumeMusic(volume);
                        while (paused) {
                            lock.unlock(); // Unlock to allow state updates
                            //SDL_Delay(100);
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                            lock.lock();

                            // Allow `next` or `previous` commands while paused
                            if (!playing) {
                                quit = true;
                                break;
                            }
                        }
                        if (!playing || quit) {
                            quit = true;
                            break;
                        }
                    }
                }
            }
        }
        av_packet_unref(&packet);

        // Allow early exit while reading packets
        {
            std::unique_lock<std::recursive_mutex> lock(stateMutex);
            if (!playing || quit) {
                quit = true;
                break;
            }
        }
    }
    av_free(buffer);
    av_frame_free(&frameYUV);
    av_frame_free(&frame);
    sws_freeContext(swsContext);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Stop music and clean up
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
    avcodec_free_context(&videoCodecContext);
    avformat_close_input(&formatContext);
}

void PlayingMedia::setVolume(const int &value){
    volume = value;
}

int PlayingMedia::getVolume() const {
    return volume;
}

// // Audio callback function for SDL
// void audioCallback(void* userdata, uint8_t* stream, int len) {
//     AVCodecContext* audioCodecContext = (AVCodecContext*)userdata;

//     int16_t* out_stream = (int16_t*)stream;
//     int len_in_samples = len / sizeof(int16_t);
//     static AVPacket* audioPacket = nullptr;
//     static uint8_t* audioBuffer = nullptr;
//     static unsigned int audioBufferIndex = 0;
//     static unsigned int audioBufferSize = 0;

//     while (len_in_samples > 0) {
//         if (audioBufferIndex >= audioBufferSize) {
//             // Get more audio data
//             if (audioPacket) {
//                 av_packet_unref(audioPacket);
//                 audioPacket = nullptr;
//             }
//             if (!audioQueue.empty()) {
//                 std::unique_lock<std::mutex> lock(audioQueueMutex);
//                 audioPacket = audioQueue.front();
//                 audioQueue.pop();
//                 lock.unlock();
//             }

//             if (audioPacket) {
//                 int ret = avcodec_send_packet(audioCodecContext, audioPacket);
//                 if (ret < 0) {
//                     av_packet_unref(audioPacket);
//                     audioPacket = nullptr;
//                     continue;
//                 }
//                 AVFrame* audioFrame = av_frame_alloc();
//                 ret = avcodec_receive_frame(audioCodecContext, audioFrame);
//                 if (ret < 0) {
//                     av_frame_free(&audioFrame);
//                     continue;
//                 }

//                 // Resample audio data (example using libswresample)
//                 SwrContext* swr_ctx = swr_alloc_set_opts(nullptr,
//                                          audio_out_channel_layout, audio_out_sample_fmt, audio_out_sample_rate,
//                                          av_get_default_channel_layout(audioFrame->channels),
//                                          (AVSampleFormat)audioFrame->format, audioFrame->sample_rate,
//                                          0, nullptr);
//                 if (!swr_ctx || swr_init(swr_ctx) < 0) {
//                     std::cerr << "Failed to initialize the resampling context\n";
//                     av_frame_free(&audioFrame);
//                     continue;
//                 }

//                 // Calculate output buffer size
//                 unsigned int out_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx, audioFrame->sample_rate) + audioFrame->nb_samples,
//                                                     audio_out_sample_rate, audioFrame->sample_rate, AV_ROUND_UP);
//                 unsigned int out_buffer_size = av_samples_get_buffer_size(nullptr, audio_out_channels, out_nb_samples, audio_out_sample_fmt, 0);

//                 // Allocate or reallocate the audio buffer if needed
//                 if (!audioBuffer || audioBufferSize < out_buffer_size) {
//                     av_free(audioBuffer); // Free the previous buffer if it exists
//                     audioBuffer = (uint8_t*)av_malloc(out_buffer_size); // Allocate new buffer
//                     audioBufferSize = out_buffer_size;
//                 }

//                 // Resample
//                 uint8_t* out_buffer[1] = { audioBuffer };
//                 swr_convert(swr_ctx, out_buffer, out_nb_samples, (const uint8_t**)audioFrame->data, audioFrame->nb_samples);

//                 audioBufferIndex = 0;

//                 swr_free(&swr_ctx);
//                 av_frame_free(&audioFrame);
//             }
//             else {
//                 // No more audio data, fill with silence
//                 memset(out_stream, 0, len_in_samples * sizeof(int16_t));
//                 return;
//             }
//         }

//         // Copy data to SDL's audio buffer
//         int amount = std::min((int)(audioBufferSize - audioBufferIndex), len_in_samples * (int)sizeof(int16_t));
//         memcpy(out_stream, (uint8_t*)audioBuffer + audioBufferIndex, amount);
//         len_in_samples -= amount / sizeof(int16_t);
//         out_stream += amount / sizeof(int16_t);
//         audioBufferIndex += amount;
//     }
// }

// void PlayingMedia::playVideo(const char* filePath) {
//     avformat_network_init();
//     AVFormatContext* formatContext = nullptr;

//     if (avformat_open_input(&formatContext, filePath, nullptr, nullptr) != 0) {
//         std::cerr << "Failed to open video file: " << filePath << "\n";
//         return;
//     }

//     if (avformat_find_stream_info(formatContext, nullptr) < 0) {
//         avformat_close_input(&formatContext);
//         std::cerr << "Failed to retrieve stream info.\n";
//         return;
//     }

//     int videoStreamIndex = -1;
//     int audioStreamIndex = -1;
//     for (unsigned i = 0; i < formatContext->nb_streams; ++i) {
//         if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && videoStreamIndex == -1) {
//             videoStreamIndex = i;
//         }
//         else if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && audioStreamIndex == -1) {
//             audioStreamIndex = i;
//         }
//     }

//     if (videoStreamIndex == -1) {
//         avformat_close_input(&formatContext);
//         std::cerr << "No video stream found.\n";
//         return;
//     }

//     // Video codec
//     AVCodecParameters* videoCodecParams = formatContext->streams[videoStreamIndex]->codecpar;
//     AVCodec* videoCodec = avcodec_find_decoder(videoCodecParams->codec_id);
//     if (!videoCodec) {
//         avformat_close_input(&formatContext);
//         std::cerr << "Unsupported video codec.\n";
//         return;
//     }

//     AVCodecContext* videoCodecContext = avcodec_alloc_context3(videoCodec);
//     avcodec_parameters_to_context(videoCodecContext, videoCodecParams);
//     if (avcodec_open2(videoCodecContext, videoCodec, nullptr) < 0) {
//         avcodec_free_context(&videoCodecContext);
//         avformat_close_input(&formatContext);
//         std::cerr << "Failed to open video codec.\n";
//         return;
//     }

//     // Audio codec
//     AVCodecContext* audioCodecContext = nullptr;
//     if (audioStreamIndex != -1) {
//         AVCodecParameters* audioCodecParams = formatContext->streams[audioStreamIndex]->codecpar;
//         AVCodec* audioCodec = avcodec_find_decoder(audioCodecParams->codec_id);
//         if (!audioCodec) {
//             std::cerr << "Unsupported audio codec.\n";
//         }
//         else {
//             audioCodecContext = avcodec_alloc_context3(audioCodec);
//             avcodec_parameters_to_context(audioCodecContext, audioCodecParams);
//             if (avcodec_open2(audioCodecContext, audioCodec, nullptr) < 0) {
//                 avcodec_free_context(&audioCodecContext);
//                 std::cerr << "Failed to open audio codec.\n";
//             }
//         }
//     }

//     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
//         avcodec_free_context(&videoCodecContext);
//         if (audioCodecContext) {
//             avcodec_free_context(&audioCodecContext);
//         }
//         avformat_close_input(&formatContext);
//         throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
//     }

//     // SDL Audio setup
//     SDL_AudioSpec wanted_spec, obtained_spec;
//     wanted_spec.freq = audio_out_sample_rate;
//     wanted_spec.format = AUDIO_S16SYS;
//     wanted_spec.channels = audio_out_channels;
//     wanted_spec.silence = 0;
//     wanted_spec.samples = 1024;
//     wanted_spec.callback = audioCodecContext ? audioCallback : nullptr;
//     wanted_spec.userdata = audioCodecContext;

//     if (SDL_OpenAudio(&wanted_spec, &obtained_spec) < 0) {
//         std::cerr << "Failed to open audio device: " << SDL_GetError() << "\n";
//         avcodec_free_context(&videoCodecContext);
//         if (audioCodecContext) {
//             avcodec_free_context(&audioCodecContext);
//         }
//         avformat_close_input(&formatContext);
//         return;
//     }

//     // Start playing audio
//     if (audioCodecContext) {
//         SDL_PauseAudio(0);
//     }

//     SDL_Window* window = SDL_CreateWindow("Video Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//                                           videoCodecContext->width, videoCodecContext->height, SDL_WINDOW_SHOWN);
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
//                                              videoCodecContext->width, videoCodecContext->height);

//     SwsContext* swsContext = sws_getContext(videoCodecContext->width, videoCodecContext->height, videoCodecContext->pix_fmt,
//                                             videoCodecContext->width, videoCodecContext->height, AV_PIX_FMT_YUV420P,
//                                             SWS_BILINEAR, nullptr, nullptr, nullptr);

//     AVFrame* frame = av_frame_alloc();
//     AVFrame* frameYUV = av_frame_alloc();
//     int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, videoCodecContext->width, videoCodecContext->height, 1);
//     uint8_t* buffer = (uint8_t*)av_malloc(bufferSize);
//     av_image_fill_arrays(frameYUV->data, frameYUV->linesize, buffer, AV_PIX_FMT_YUV420P,
//                          videoCodecContext->width, videoCodecContext->height, 1);

//     AVPacket packet;
//     bool quit = false;

//     // Calculate frame delay
//     double frameDelay = 40.0; // Default for ~25 FPS
//     if (formatContext->streams[videoStreamIndex]->avg_frame_rate.num > 0) {
//         double fps = av_q2d(formatContext->streams[videoStreamIndex]->avg_frame_rate);
//         frameDelay = 1000.0 / fps; // Convert to milliseconds
//     }

//     while (av_read_frame(formatContext, &packet) >= 0 && !quit) {
//         if (packet.stream_index == videoStreamIndex) {
//             if (avcodec_send_packet(videoCodecContext, &packet) == 0) {
//                 while (avcodec_receive_frame(videoCodecContext, frame) == 0) {
//                     sws_scale(swsContext, frame->data, frame->linesize, 0, videoCodecContext->height,
//                               frameYUV->data, frameYUV->linesize);

//                     SDL_UpdateYUVTexture(texture, nullptr,
//                                          frameYUV->data[0], frameYUV->linesize[0],
//                                          frameYUV->data[1], frameYUV->linesize[1],
//                                          frameYUV->data[2], frameYUV->linesize[2]);

//                     SDL_RenderClear(renderer);
//                     SDL_RenderCopy(renderer, texture, nullptr, nullptr);
//                     SDL_RenderPresent(renderer);

//                     // Delay to control frame rate
//                     //SDL_Delay(static_cast<int>(frameDelay));
//                     std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(frameDelay)));

//                     // Handle SDL events and playback state
//                     SDL_Event event;
//                     while (SDL_PollEvent(&event)) {
//                         if (event.type == SDL_QUIT) {
//                             quit = true;
//                         }
//                     }

//                     // Check `paused` and `playing` state
//                     {
//                         std::unique_lock<std::recursive_mutex> lock(stateMutex);
//                         while (paused) {
//                             lock.unlock(); // Unlock to allow state updates
//                             //SDL_Delay(100);
//                             std::this_thread::sleep_for(std::chrono::milliseconds(100));
//                             lock.lock();

//                             // Allow `next` or `previous` commands while paused
//                             if (!playing) {
//                                 quit = true;
//                                 break;
//                             }
//                         }
//                         if (!playing || quit) {
//                             quit = true;
//                             break;
//                         }
//                     }
//                 }
//             }
//         }
//         else if (packet.stream_index == audioStreamIndex && audioCodecContext) {
//             // Queue audio packet for the audio thread
//             AVPacket* new_packet = av_packet_alloc();
//             if (av_packet_ref(new_packet, &packet) < 0) {
//                 std::cerr << "Failed to copy audio packet\n";
//             }
//             else {
//                 std::unique_lock<std::mutex> lock(audioQueueMutex);
//                 audioQueue.push(new_packet);
//                 lock.unlock();
//             }
//         }
//         av_packet_unref(&packet);

//         // Allow early exit while reading packets
//         {
//             std::unique_lock<std::recursive_mutex> lock(stateMutex);
//             if (!playing || quit) {
//                 quit = true;
//                 break;
//             }
//         }
//     }

//     // Flush audio queue
//     {
//         std::unique_lock<std::mutex> lock(audioQueueMutex);
//         while (!audioQueue.empty()) {
//             av_packet_free(&audioQueue.front());
//             audioQueue.pop();
//         }
//     }

//     av_free(buffer);
//     av_frame_free(&frameYUV);
//     av_frame_free(&frame);
//     sws_freeContext(swsContext);
//     SDL_DestroyTexture(texture);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_CloseAudio();
//     SDL_Quit();
//     avcodec_free_context(&videoCodecContext);
//     if (audioCodecContext) {
//         avcodec_free_context(&audioCodecContext);
//     }
//     avformat_close_input(&formatContext);
// }



// void PlayingMedia::setVolume(const int &value){
//     volume = value;
// }

// int PlayingMedia::getVolume() const {
//     return volume;
// }


