// #ifndef PLAYING_MEDIA_VIEW_H
// #define PLAYING_MEDIA_VIEW_H

// #include "BaseView.hpp"
// #include "MediaFile.hpp"
// #include <iostream>
// #include <memory>

// enum PlayingMediaMenu {
//     BACK_FROM_PLAYING,
//     PLAY,
//     PAUSE,
//     NEXT,
//     PREV
// };

// class PlayingMediaView : public BaseView {
// public:
//     void showMenu() override;
//     void hideMenu() override;
//     void showSongInfo(const std::shared_ptr<MediaFile>& file, size_t currentTime, size_t totalTime);
//     ~PlayingMediaView() override = default;
// };

// #endif // PLAYING_MEDIA_VIEW_H


#ifndef PLAYING_MEDIA_VIEW_H
#define PLAYING_MEDIA_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>

#include "MediaFile.hpp"
#include <iostream>
#include <memory>

enum PlayingMediaMenu {
    PLAY,
    PAUSE,
    NEXT,
    PREV,
    BACK_FROM_PLAYING
};

class PlayingMediaView : public BaseView {
private:
    std::vector<std::string> menu_entries = {
        "Play",
        "Pause",
        "Next Song",
        "Previous Song",
        "Go Back"
    };
    int selected_option = 0; // Lưu lựa chọn của người dùng

public:
    void showMenu() override;
    int getSelectedOption() const ;
    ~PlayingMediaView() override = default;
    void hideMenu() override;
    void showSongInfo(const std::shared_ptr<MediaFile>& file, size_t currentTime, size_t totalTime);

};

#endif // PLAYING_MEDIA_VIEW_H