// #ifndef PLAYLIST_VIEW_H
// #define PLAYLIST_VIEW_H

// #include <vector>
// #include <string>
// #include "BaseView.hpp"
// #include "Playlist.hpp"

// enum PlaylistMenu {
//     BACK_FROM_PLAYLIST,
//     SELECT_PLAYLIST,
//     ADD_PLAYLIST,
//     REMOVE_PLAYLIST
// };

// enum PlaylistStatus {
//     PLAYLIST_NORMAL,
//     PLAYLIST_SELECT_STATUS,
//     PLAYLIST_ADD_STATUS,
//     PLAYLIST_REMOVE_STATUS,
// };

// class PlaylistView : public BaseView {
// public:
//     void showMenu() override;
//     void hideMenu() override;
//     void showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists);
//     ~PlaylistView() override = default;
//     void displayStatusMessage(PlaylistStatus& status);
// };
// #endif // PLAYLIST_VIEW_H

#ifndef PLAYLIST_VIEW_H
#define PLAYLIST_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>
#include "Playlist.hpp"
enum PlaylistStatus {
    PLAYLIST_NORMAL,
    PLAYLIST_SELECT_STATUS,
    PLAYLIST_ADD_STATUS,
    PLAYLIST_REMOVE_STATUS,
};

enum PlaylistMenu {
    SELECT_PLAYLIST,
    ADD_PLAYLIST,
    REMOVE_PLAYLIST,
    BACK_FROM_PLAYLIST
};

class PlaylistView : public BaseView {
private:
    std::vector<std::string> menu_entries = {
        "Select a Playlist",
        "Add a Playlist",
        "Remove a Playlist",
        "Go Back"
    };
    int selected_option = 0;

public:
    void showMenu() override;
    int getSelectedOption() const; // Hàm trả về lựa chọn của người dùng
    ~PlaylistView() override = default;
    void hideMenu() override;
    void showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists);
    void displayStatusMessage(PlaylistStatus& status);
};

#endif // PLAYLIST_VIEW_H
