#include "PlayingMedia.hpp"

std::shared_ptr<MediaFile> PlayingMedia::getCurrentMediaFile() const {
    return currentMediaFile;
}

void PlayingMedia::setCurrentMediaFile(const std::shared_ptr<MediaFile>& mediaFile) {
    currentMediaFile = mediaFile;
}

int PlayingMedia::getCurrentTime() const {
    return currentTime;
}

void PlayingMedia::setCurrentTime(int time) {
    currentTime = time;
}

bool PlayingMedia::getIsPlaying() const {
    return isPlaying;
}

void PlayingMedia::setIsPlaying(bool playing) {
    isPlaying = playing;
}
