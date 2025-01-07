#ifndef PLAYING_MEDIA_CONTROLLER_H
#define PLAYING_MEDIA_CONTROLLER_H

#include "MediaFile.hpp"

class PlayingMediaController {
public:
    void playMediaFile(MediaFile file);
    void play();
    void pause();
    void stop();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(int level);
};

#endif // PLAYING_MEDIA_CONTROLLER_H
