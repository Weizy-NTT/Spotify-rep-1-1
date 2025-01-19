// #ifndef DETAILED_PLAYLIST_VIEW_H
// #define DETAILED_PLAYLIST_VIEW_H

// #include "BaseView.hpp"
// #include "Playlist.hpp"
// #include <iostream>
// #include <vector>
// #include <memory>

// enum DetailedPlaylistMenu {
//     BACK_FROM_DETAIL,
//     PLAY_SONG_FROM_PLAYLIST,
//     ADD_SONG,
//     DELETE_SONG,
//     SHOW_DETAIL_SONG
// };

// enum DetailedPlaylistStatus {
//     DETAILED_NORMAL,
//     DETAILED_ADD_STATUS,
//     DETAILED_PLAY_STATUS,
//     DETAILED_DELETE_STATUS,
//     DETAILED_SHOW_STATUS,
// };

// class DetailedPlaylistView : public BaseView {
// public:
//     void showMenu() override;
//     void hideMenu() override;
//     void showPlaylistDetails(const std::shared_ptr<Playlist>& playlist);
//     void showListOfSongs(const std::shared_ptr<Playlist>& playlist);
//     void displayStatusMessage(DetailedPlaylistStatus& status);
// };

// #endif // DETAILED_PLAYLIST_VIEW_H

#ifndef DETAILED_PLAYLIST_VIEW_H
#define DETAILED_PLAYLIST_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>
#include <memory>
#include "Playlist.hpp"


enum DetailedPlaylistMenu {
    PLAY_SONG_FROM_PLAYLIST,
    ADD_SONG,
    DELETE_SONG,
    SHOW_DETAIL_SONG,
    BACK_FROM_DETAIL
};

enum DetailedPlaylistStatus {
    DETAILED_NORMAL,
    DETAILED_ADD_STATUS,
    DETAILED_PLAY_STATUS,
    DETAILED_DELETE_STATUS,
    DETAILED_SHOW_STATUS,
};


class DetailedPlaylistView : public BaseView {
private:
    std::vector<std::string> menu_entries = {
        "Play a song",
        "Add a song to playlist",
        "Delete a song from playlist",
        "Show details of a song",
        "Go Back"
    };
    int selected_option = 0;

public:
    void showMenu() override;
    void hideMenu() override;
    void showPlaylistDetails(const std::shared_ptr<Playlist>& playlist);
    void showListOfSongs(const std::shared_ptr<Playlist>& playlist);
    void displayStatusMessage(DetailedPlaylistStatus& status);
    int getSelectedOption() const; // Hàm trả về lựa chọn của người dùng
    ~DetailedPlaylistView() override = default;
};

#endif // DETAILED_PLAYLIST_VIEW_H
