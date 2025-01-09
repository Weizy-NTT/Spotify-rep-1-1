#ifndef PLAYING_MEDIA_VIEW_H
#define PLAYING_MEDIA_VIEW_H

#include "BaseView.hpp"
#include "MediaFile.hpp"
#include <iostream>

enum PlayingMediaMenu {
    BACK_FROM_PLAYING,
    PLAY_PAUSE,
    NEXT,
    PREV,
    
};

class PlayingMediaView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showSongInfo(const MediaFile& file);
    ~PlayingMediaView() override = default;
};

#endif // PLAYING_MEDIA_VIEW_H
