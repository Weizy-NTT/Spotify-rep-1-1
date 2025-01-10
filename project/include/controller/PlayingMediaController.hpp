#ifndef PLAYING_MEDIA_CONTROLLER_H
#define PLAYING_MEDIA_CONTROLLER_H

#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "ControllerManager.hpp"

class PlayingMediaController : public BaseController {
public:
    void handleInput();
    void playMediaFile(MediaFile file);
    void play();
    void pause();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(int level);
    void back();
};

#endif // PLAYING_MEDIA_CONTROLLER_H
