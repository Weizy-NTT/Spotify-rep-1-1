#ifndef PLAYING_MEDIA_H
#define PLAYING_MEDIA_H

#include "MediaFile.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>

namespace fs = std::filesystem;

class PlayingMedia {
private:
    std::vector<std::shared_ptr<MediaFile>> currentplaylist;
    Mix_Music *currentMusic = nullptr;
    bool isPaused = false;
    size_t volume;
    size_t currentTime;
    size_t currentTrackIndex = 0;

public:
    PlayingMedia();
    std::shared_ptr<MediaFile> getCurrentMediaFile() const;
    void setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile);
    size_t getCurrentTime() const;
    void setCurrentTime(int time);
    void play(const std::string &filePath);
    bool isPause() const;
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void nextTrack();
    void previousTrack();
    bool hasNextTrack() const;
    bool hasPrevTrack() const;
    void playCurrentTrack();
    void setPlaylist(const std::vector<std::shared_ptr<MediaFile>>& newPlaylist);
    void adjustVolume(int newVolume);
    ~PlayingMedia();
};

#endif // PLAYING_MEDIA_H
