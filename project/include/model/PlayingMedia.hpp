#ifndef PLAYING_MEDIA_H
#define PLAYING_MEDIA_H

#include "MediaFile.hpp"
#include <memory>

class PlayingMedia {
private:
    std::shared_ptr<MediaFile> currentMediaFile;
    int currentTime;
    bool isPlaying;

public:
    std::shared_ptr<MediaFile> getCurrentMediaFile() const;
    void setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile);
    int getCurrentTime() const;
    void setCurrentTime(int time);
    bool getIsPlaying() const;
    void setIsPlaying(bool playing);
};

#endif // PLAYING_MEDIA_H
