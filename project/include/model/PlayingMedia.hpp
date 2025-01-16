#ifndef PLAYING_MEDIA_H
#define PLAYING_MEDIA_H

#include "MediaFile.hpp"
#include <memory>
#include <filesystem>
#include <atomic>
#include <mutex>
#include <stdint.h>
#include <thread>

namespace fs = std::filesystem;

void audioCallback(void* userdata, uint8_t* stream, int len);

class PlayingMedia {
private:
    std::vector<std::shared_ptr<MediaFile>> currentplaylist;
    //Mix_Music *currentMusic = nullptr;
    size_t volume;
    size_t currentTime = 0;
    size_t totalTime = 0;
    size_t currentTrackIndex = -1;
    std::atomic<bool> paused{false};
    std::atomic<bool> playing{false};
    std::thread playbackThread;
    std::recursive_mutex stateMutex; // Allow recursive locking
public:
    PlayingMedia();
    std::shared_ptr<MediaFile> getCurrentMediaFile() const;
    void setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile);
    size_t getCurrentTime() const;
    size_t getTotalTime() const;
    void setCurrentTime(size_t time);
    void playAudio(const char* filePath);
    void playVideo(const char* filePath);
    bool isPlaying();
    void play();
    void pauseMusic();
    void resumeMusic();
    void stop();
    void nextTrack();
    void previousTrack();
    bool hasNextTrack() const;
    bool hasPrevTrack() const;
    void playCurrentTrack();
    void setPlaylist(const std::vector<std::shared_ptr<MediaFile>>& newPlaylist);
    void adjustVolume(size_t newVolume);

    void stopPlaybackThread();
    
    ~PlayingMedia();
};

#endif // PLAYING_MEDIA_H
