#ifndef PLAYING_MEDIA_VIEW_H
#define PLAYING_MEDIA_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>
#include <functional>
#include "MediaFile.hpp"
#include <iostream>
#include <memory>
#include <PlayingMedia.hpp>

// Enum for playing media menu options
enum PlayingMediaMenu {
    PLAY,                   // Option to play the current media
    PAUSE,                  // Option to pause playback
    NEXT,                   // Option to skip to the next song
    PREV,                   // Option to skip to the previous song
    BACK_FROM_PLAYING       // Option to go back to the previous menu
};

class PlayingMediaView : public BaseView {
private:
    // Menu entries for the playing media view
    std::vector<std::string> menu_entries = {
        "Play",
        "Pause",
        "Next Song",
        "Previous Song",
        "Go Back"
    };
    int selected_option = 0; // Variable to store the user's selected option

public:
    // Override to display the menu
    void showMenu() override;

    // Getter to retrieve the user's selected option
    int getSelectedOption() const;

    // Destructor
    ~PlayingMediaView() override = default;

    // Override to hide the menu
    void hideMenu() override;
    void showPlayingMedia(PlayingMedia* player, size_t& currentTime, size_t totalTime, int& volume) ;
};

#endif // PLAYING_MEDIA_VIEW_H
