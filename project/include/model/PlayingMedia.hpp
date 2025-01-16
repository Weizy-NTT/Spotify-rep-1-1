#ifndef PLAYING_MEDIA_H
#define PLAYING_MEDIA_H

#include "MediaFile.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>
#include <atomic>

namespace fs = std::filesystem;

class PlayingMedia {
private:
    std::vector<std::shared_ptr<MediaFile>> currentplaylist;
    Mix_Music *currentMusic = nullptr;
    size_t volume;
    size_t currentTime = 0;
    size_t totalTime = 0;
    size_t currentTrackIndex = -1;
    std::atomic<bool> paused{false};
public:
    PlayingMedia();
    std::shared_ptr<MediaFile> getCurrentMediaFile() const;
    void setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile);
    size_t getCurrentTime() const;
    size_t getTotalTime() const;
    void setCurrentTime(size_t time);
    void play(const std::string &filePath);
    bool isPlaying();
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void nextTrack();
    void previousTrack();
    bool hasNextTrack() const;
    bool hasPrevTrack() const;
    void playCurrentTrack();
    void setPlaylist(const std::vector<std::shared_ptr<MediaFile>>& newPlaylist);
    void adjustVolume(size_t newVolume);
    std::string extractAudio(const std::string &videoPath);
    
    ~PlayingMedia();
};

#endif // PLAYING_MEDIA_H
