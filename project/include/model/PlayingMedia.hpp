#ifndef PLAYING_MEDIA_H
#define PLAYING_MEDIA_H

#include "MediaFile.hpp"
#include <memory>
#include <filesystem>
#include <atomic>
#include <mutex>
#include <stdint.h>
#include <thread>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/imgutils.h>
#include <libavutil/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
}

namespace fs = std::filesystem;

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
    AVCodecContext* audioCodecContext = nullptr;
    PlayingMedia();
    std::shared_ptr<MediaFile> getCurrentMediaFile() const;
    void setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile);
    size_t getCurrentTime() const;
    size_t getTotalTime() const;
    void setCurrentTime(size_t time);
    void playAudio(const char* filePath);
    void playVideo(const char* filePath, const char* wavPath);
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
    void setVolume(const int &value);
    int getVolume() const;
    void stopPlaybackThread();
    std::string extractAudio(const std::string &videoPath);

    ~PlayingMedia();
};

#endif // PLAYING_MEDIA_H
