#include "PlayingMedia.hpp"
#include <iostream>
#include "ControllerManager.hpp"
std::mutex mediaMutex;

std::shared_ptr<MediaFile> PlayingMedia::getCurrentMediaFile() const {
    if (currentplaylist.empty() || currentTrackIndex < 0 || currentTrackIndex >= currentplaylist.size()){
        return nullptr;
    } 
    return currentplaylist[currentTrackIndex];
}

// void PlayingMedia::setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile) {
//     if (!mediaFile) {
//         std::cerr << "Error: Invalid media file." << std::endl;
//         return;
//     }

//     // Kiểm tra nếu bài hát này đã có trong playlist
//     for (size_t i = 0; i < currentplaylist.size(); ++i) {
//         if (currentplaylist[i]->getID() == mediaFile->getID()) {
//             currentTrackIndex = i;  // Lưu lại chỉ số bài hát
//             stopMusic();  // Dừng nhạc nếu có nhạc đang phát 
//             return;
//         }
//     }

//     // Nếu không tìm thấy bài hát trong playlist, reset chỉ số và playlist
//     currentTrackIndex = -1;  // Không tìm thấy bài hát này
// }

void PlayingMedia::setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile) {
    if (!mediaFile) {
        std::cerr << "Error: Invalid media file." << std::endl;
        return;
    }
    if (!getCurrentMediaFile() || (mediaFile->getID() != getCurrentMediaFile()->getID())) {
        for (size_t i = 0; i < currentplaylist.size(); ++i) {
            if (currentplaylist[i]->getID() == mediaFile->getID()) {
                stopMusic();
                currentTrackIndex = i;  // Lưu lại chỉ số bài hát
                playCurrentTrack();
                //stop?
                return;
            }
        }
    }
}

void PlayingMedia::setPlaylist(const std::vector<std::shared_ptr<MediaFile>>& newPlaylist) 
{
    if (newPlaylist != currentplaylist) {
        stopMusic();  // Dừng nhạc nếu có nhạc đang phát
        currentplaylist = newPlaylist;
        currentTrackIndex = -1;  // Đặt chỉ số bài hát hiện tại là -1 hoặc một giá trị hợp lý
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
    if(SDL_Init(SDL_INIT_AUDIO) < 0){
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    instance = this;
    Mix_HookMusicFinished(whenMusicFinished);
}

PlayingMedia::~PlayingMedia(){
    isPlayingMediaFile.store(false, std::memory_order_relaxed);
    if (updateThread.joinable()) {
        updateThread.join();
    }
    if(currentMusic){
        Mix_FreeMusic(currentMusic);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void PlayingMedia::play(const std::string &filePath){
    stopMusic(); // Stop any currently Playing music
    currentMusic = Mix_LoadMUS(filePath.c_str());
    totalTime = getCurrentMediaFile()->getDuration();
    currentTime = 0;
    isPlayingMediaFile.store(true, std::memory_order_relaxed);
    updateThread = std::thread(&PlayingMedia::updateElapsedTime, this);
    if(!currentMusic){
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return;
    }

    if(Mix_PlayMusic(currentMusic, 1) == -1){
        std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }
}

void PlayingMedia::pauseMusic(){
    if(Mix_PlayingMusic() && !Mix_PausedMusic()){
        Mix_PauseMusic();
        isPlayingMediaFile.store(false, std::memory_order_relaxed);
    }
}

void PlayingMedia::resumeMusic(){
    if(Mix_PausedMusic()){
        Mix_ResumeMusic();
        if (!isPlayingMediaFile.load(std::memory_order_relaxed)) {
            isPlayingMediaFile.store(true, std::memory_order_relaxed);
            if (updateThread.joinable()) {
                updateThread.join(); // Đảm bảo luồng cũ đã kết thúc trước khi khởi động lại
            }
            updateThread = std::thread(&PlayingMedia::updateElapsedTime, this); // Khởi động lại luồng
        }
    }
}

void PlayingMedia::togglePlayPause() {
    if (Mix_PausedMusic()) {
        resumeMusic();
    } else {
        pauseMusic();
    }
}

void PlayingMedia::stopMusic(){
    isPlayingMediaFile.store(false, std::memory_order_relaxed);

    if (updateThread.joinable()) { 
        updateThread.join(); // Chờ thread kết thúc
    }
    
    if(Mix_PlayingMusic()){
        Mix_HaltMusic();
    }
    if(currentMusic){
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }
}

int PlayingMedia::isPlaying() {
    if (Mix_PlayingMusic()) {
        // Kiểm tra nếu nhạc đang phát
        return 1;
    } else if (Mix_PausedMusic()) {
        // Kiểm tra nếu nhạc đang tạm dừng
        return 2;
    } else {
        // Nếu không có nhạc nào đang phát hoặc tạm dừng
        return 0;
    }
}

void PlayingMedia::adjustVolume(size_t newVolume){
    volume = newVolume;
    Mix_VolumeMusic(volume);
    std::cout<< "Volume set to: " << volume << "\n";
}

void PlayingMedia::playCurrentTrack(){
    if(!currentplaylist.empty()){
        std::string currentTrackPath;
        if (currentplaylist[currentTrackIndex]->getType() == MediaType::AUDIO) {
            currentTrackPath = currentplaylist[currentTrackIndex]->getPath();
        }
        else {
            std::string wavFilePath = extractAudio(currentplaylist[currentTrackIndex]->getPath());
            if (!wavFilePath.empty()) {
                currentTrackPath = wavFilePath;
            }
        }
        play(currentTrackPath);
    } else {
        std::cerr <<"No tracks available to play.\n";
    }
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

void PlayingMedia::nextTrack() {
    Mix_HookMusicFinished(nullptr);
    if (!currentplaylist.empty() && hasNextTrack()) {
        currentTrackIndex++;
        playCurrentTrack();
    } else {
        stopMusic();
    }
    Mix_HookMusicFinished(whenMusicFinished);
}

void PlayingMedia::previousTrack() {
    Mix_HookMusicFinished(nullptr);
    if (!currentplaylist.empty() && hasPrevTrack()) {
        currentTrackIndex--;
        playCurrentTrack();
    } else {
        stopMusic();
    }
    Mix_HookMusicFinished(whenMusicFinished);
}

bool PlayingMedia::hasNextTrack() const {
    return currentTrackIndex >= 0 && currentTrackIndex < currentplaylist.size() - 1;
}

bool PlayingMedia::hasPrevTrack() const {
    return currentTrackIndex > 0 && currentTrackIndex < currentplaylist.size();
}

PlayingMedia* PlayingMedia::instance = nullptr;

void PlayingMedia::whenMusicFinished() {
    if (instance) {
        instance->autoNextTrack();
    }
}

void PlayingMedia::autoNextTrack() {
    if (!currentplaylist.empty() && hasNextTrack()) {
        currentTrackIndex++;
        playCurrentTrack();
    } else {
        stopMusic();
    }
}

void PlayingMedia::updateElapsedTime() {
    while (isPlayingMediaFile.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (currentTime < totalTime) {
            ++currentTime;
            if (getPlayingView()) {
                ControllerManager::getInstance()->getPlayingMediaController()->updateTime();
            }
        } else {
            isPlayingMediaFile.store(false, std::memory_order_relaxed);
        }
    }
}

void PlayingMedia::setPlayingView(bool status) {
    isPlayingView.store(status, std::memory_order_relaxed);
}

bool PlayingMedia::getPlayingView() {
    return isPlayingView.load(std::memory_order_relaxed);
}

