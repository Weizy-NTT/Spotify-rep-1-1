#ifndef PLAYING_MEDIA_H
#define PLAYING_MEDIA_H

#include "MediaFile.hpp"

class PlayingMedia {
private:
    MediaFile* currentMediaFile;
    int currentTime;
    bool isPlaying;

public:
    MediaFile* getCurrentMediaFile() const;
    void setCurrentMediaFile(MediaFile* mediaFile);
    int getCurrentTime() const;
    void setCurrentTime(int time);
    bool getIsPlaying() const;
    void setIsPlaying(bool playing);
    void play();
    void pause();
    void stop();
    void skiptoNext();
    void skiptoPrevious();
    void skipForward(int seconds);
    void skipBackward(int seconds);
};

#endif // PLAYING_MEDIA_H
