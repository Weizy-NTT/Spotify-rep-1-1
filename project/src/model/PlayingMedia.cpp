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

void PlayingMedia::setCurrentTime(int time) {
    currentTime = time;
}


PlayingMedia::PlayingMedia() : volume(50){
    if(SDL_Init(SDL_INIT_AUDIO) < 0){
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
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

void PlayingMedia::adjustVolume(int newVolume){
    volume = newVolume;
    Mix_VolumeMusic(volume);
    std::cout<< "Volume set to: " << volume << "\n";
}

void PlayingMedia::playCurrentTrack(){
    if(!currentplaylist.empty()){
        std::string currentTrackPath = currentplaylist[currentTrackIndex]->getPath();
        play(currentTrackPath);
    } else {
        std::cerr <<"No tracks available to play.\n";
    }
}

void PlayingMedia::nextTrack() {
    if (!currentplaylist.empty() && hasNextTrack()) {
        currentTrackIndex++;
        playCurrentTrack();
    } else {
        std::cerr << "No next track available.\n";
    }
}

void PlayingMedia::previousTrack() {
    if (!currentplaylist.empty() && hasPrevTrack()) {
        currentTrackIndex--;
        playCurrentTrack();
    } else {
        std::cerr << "No previous track available.\n";
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
        std::cout << "TRack finished. Moving to next track....\n";
        instance->nextTrack();
    }
}