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
    std::atomic<bool> isPlayingView{false};      
public:
    void updateElapsedTime();

    void handleInput(const std::string& ID);

    void playMediaFile(const std::shared_ptr<MediaFile>& file);

    void play();

    void pause();

    void skipToNext();

    void skipToPrevious();

    void adjustVolume(size_t level);

    void updateTime();

    virtual void startUpdateThread();

    virtual void stopUpdateThread();

    void back();
};

#endif // PLAYING_MEDIA_CONTROLLER_H
