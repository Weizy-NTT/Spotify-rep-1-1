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
    std::vector<std::shared_ptr<MediaFile>> currentplaylist; // Current playlist of media files
    int volume;                                           // Current playback volume
    size_t currentTime = 0;                                  // Current playback time in seconds
    size_t totalTime = 0;                                    // Total playback time in seconds
    size_t currentTrackIndex = -1;                           // Index of the current track in the playlist
    std::atomic<bool> paused{false};                         // Atomic flag to indicate if playback is paused
    std::atomic<bool> playing{false};                        // Atomic flag to indicate if media is playing
    std::thread playbackThread;                              // Thread for managing playback
    std::recursive_mutex stateMutex;                         // Mutex to protect shared states (supports recursive locking)

public:
    PlayingMedia();

    // Get the currently playing media file
    std::shared_ptr<MediaFile> getCurrentMediaFile() const;

    // Set the current media file
    void setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile);
    size_t& getCurrentTime();
    std::string getDurationStringType() const;
    size_t getTotalTime() const;

    // Set the current playback time
    void setCurrentTime(size_t time);

    // Play audio from the specified file path
    void playAudio(const char* filePath);
    void playVideo(const char* videoFilePath, const char* wavPath);
    bool isPlaying();

    // Start playback
    void play();

    // Pause the current playback
    void pauseMusic();

    // Resume playback
    void resumeMusic();

    // Stop playback
    void stop();

    // Skip to the next track in the playlist
    void nextTrack();

    // Skip to the previous track in the playlist
    void previousTrack();

    // Check if there is a next track in the playlist
    bool hasNextTrack() const;

    // Check if there is a previous track in the playlist
    bool hasPrevTrack() const;

    // Play the current track in the playlist
    void playCurrentTrack();

    // Set a new playlist for playback
    void setPlaylist(const std::vector<std::shared_ptr<MediaFile>>& newPlaylist);

    // Adjust the playback volume
    void adjustVolume(size_t newVolume);
    void setVolume(const int &value);
    int& getVolume();
    void stopPlaybackThread();
    std::string extractAudio(const std::string &videoPath);
    ~PlayingMedia();
};

#endif // PLAYING_MEDIA_H
