#ifndef PLAYING_MEDIA_VIEW_H
#define PLAYING_MEDIA_VIEW_H

#include "BaseView.hpp"
#include "MediaFile.hpp"
#include <iostream>
#include <memory>

enum PlayingMediaMenu {
    BACK_FROM_PLAYING,
    PLAY,
    PAUSE,
    NEXT,
    PREV,
    VOLUME
};

class PlayingMediaView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showSongInfo(const std::shared_ptr<MediaFile>& file, size_t currentTime, size_t totalTime);
    ~PlayingMediaView() override = default;
};

#endif // PLAYING_MEDIA_VIEW_H
