#ifndef PLAYLIST_VIEW_H
#define PLAYLIST_VIEW_H

#include <vector>
#include <string>
#include "BaseView.hpp"
#include "Playlist.hpp"

enum PlaylistMenu {
    BACK_FROM_PLAYLIST,
    SELECT_PLAYLIST,
    ADD_PLAYLIST,
    REMOVE_PLAYLIST
};

enum PlaylistStatus {
    PLAYLIST_NORMAL,
    PLAYLIST_SELECT_STATUS,
    PLAYLIST_ADD_STATUS,
    PLAYLIST_REMOVE_STATUS,
};

class PlaylistView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists);
    ~PlaylistView() override = default;
    void displayStatusMessage(PlaylistStatus& status);
};
#endif // PLAYLIST_VIEW_H
