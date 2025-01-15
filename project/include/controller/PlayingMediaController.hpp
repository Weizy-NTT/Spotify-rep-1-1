#ifndef PLAYING_MEDIA_CONTROLLER_H
#define PLAYING_MEDIA_CONTROLLER_H

#include "MediaFile.hpp"
#include "BaseController.hpp"
#include <memory>

class PlayingMediaController : public BaseController {
public:
    void handleInput(const std::string& ID);
    void playMediaFile(const std::shared_ptr<MediaFile>& file);
    void play();
    void skipToNext();
    void skipToPrevious();
    void adjustVolume(size_t level);
    void updateTime();
    void back();
};

#endif // PLAYING_MEDIA_CONTROLLER_H
