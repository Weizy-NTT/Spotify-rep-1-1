#ifndef PLAYING_MEDIA_CONTROLLER_H
#define PLAYING_MEDIA_CONTROLLER_H

#include "MediaFile.hpp"
#include "BaseController.hpp"
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <PlayingMedia.hpp>
#include <stdexcept>
#include <queue>

extern std::mutex mediaMutex;

class PlayingMediaController : public BaseController {
    std::thread updateThread;
    std::atomic<bool> isPlayingMediaFile{false};
    void updateElapsedTime();
    std::mutex mutex; // Allow recursive locking
public:
    void handleInput(const std::string& ID);
    void playMediaFile(const std::shared_ptr<MediaFile>& file);
    void play();
    void pause();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(size_t level);
    void updateTime();
    void startUpdateThread();
    void stopUpdateThread();
    void back();
};

#endif // PLAYING_MEDIA_CONTROLLER_H
