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

class PlaylistView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists);
    ~PlaylistView() override = default;
};
#endif // PLAYLIST_VIEW_H
