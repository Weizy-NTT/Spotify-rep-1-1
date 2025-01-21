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

extern std::mutex mediaMutex; // Mutex for media synchronization

class PlayingMediaController : public BaseController {
    std::thread updateThread; // Thread for updating elapsed time
    std::atomic<bool> isPlayingMediaFile{false}; // Atomic flag to check if a media file is being played
    std::atomic<bool> isPlayingView{false};      // Atomic flag to check if the playing view is active
    void updateElapsedTime(); // Private method to update elapsed time during playback

public:
    // Handle user input for playing a specific media file by its ID
    void handleInput(const std::string& ID);

    // Play the specified media file
    void playMediaFile(const std::shared_ptr<MediaFile>& file);

    // Play the current media
    void play();

    // Pause the current media
    void pause();

    // Skip to the next media file in the queue
    void skipToNext();

    // Skip to the previous media file in the queue
    void skipToPrevious();

    // Adjust the playback volume to the specified level
    void adjustVolume(size_t level);

    // Update the playback time
    void updateTime();

    // Start the thread to update elapsed time
    void startUpdateThread();

    // Stop the thread that updates elapsed time
    void stopUpdateThread();

    // Navigate back to the previous menu or screen
    void back();
};

#endif // PLAYING_MEDIA_CONTROLLER_H
