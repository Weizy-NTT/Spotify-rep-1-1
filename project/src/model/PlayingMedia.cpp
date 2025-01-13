#include "PlayingMedia.hpp"
#include <iostream>

std::shared_ptr<MediaFile> PlayingMedia::getCurrentMediaFile() const {
    if (currentplaylist.empty() || currentTrackIndex < 0 || currentTrackIndex >= currentplaylist.size()){
        return nullptr;
    } 
    return currentplaylist[currentTrackIndex];
}

void PlayingMedia::setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile) {
    for (size_t i = 0;i < currentplaylist.size();i++) {
        if (currentplaylist[i]->getID() == mediaFile->getID()) {
            currentTrackIndex = i;
            return;
        }
    }  
}

void PlayingMedia::setPlaylist(const std::vector<std::shared_ptr<MediaFile>>& newPlaylist) {currentplaylist = newPlaylist;}

size_t PlayingMedia::getCurrentTime() const {
    return currentTime;
}

void PlayingMedia::setCurrentTime(size_t time) {
    currentTime = time;
}


PlayingMedia::PlayingMedia() : volume(50){
    Mix_VolumeMusic(volume);
    if(SDL_Init(SDL_INIT_AUDIO) < 0){
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    instance = this;
}

PlayingMedia::~PlayingMedia(){
    if(currentMusic){
        Mix_FreeMusic(currentMusic);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void PlayingMedia::play(const std::string &filePath){
    stopMusic(); // Stop any currently Playing music
    currentMusic = Mix_LoadMUS(filePath.c_str());
    if(!currentMusic){
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_HookMusicFinished(whenMusicFinished);
    if(Mix_PlayMusic(currentMusic, 1) == -1){
        std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }
}

void PlayingMedia::pauseMusic(){
    if(Mix_PlayingMusic() && !isPaused){
        Mix_PauseMusic();
        isPaused = true;
    }
}

void PlayingMedia::resumeMusic(){
    if(isPaused){
        Mix_ResumeMusic();
        isPaused = false;
    }
}

void PlayingMedia::togglePlayPause() {
    if (isPaused) {
        resumeMusic();
    } else {
        pauseMusic();
    }
}

void PlayingMedia::stopMusic(){
    if(Mix_PlayingMusic()){
        Mix_HaltMusic();
    }
    if(currentMusic){
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }
    isPaused = true;
}

int PlayingMedia::isPlaying() {
    return Mix_PlayingMusic();
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
    if (!currentplaylist.empty() && hasNextTrack()) {
        currentTrackIndex++;
        playCurrentTrack();
    } else {
        stopMusic();
    }
}

void PlayingMedia::previousTrack() {
    if (!currentplaylist.empty() && hasPrevTrack()) {
        currentTrackIndex--;
        playCurrentTrack();
    } else {
        stopMusic();
    }
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
        instance->nextTrack();
    }
}