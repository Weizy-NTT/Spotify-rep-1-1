#ifndef PLAYLIST_VIEW_H
#define PLAYLIST_VIEW_H

#include <vector>
#include <string>
#include "BaseView.hpp"
#include "Playlist.hpp"

namespace PlaylistMenu {
    const std::string SELECT_PLAYLIST    = "1";
    const std::string ADD_PLAYLIST       = "2";
    const std::string REMOVE_PLAYLIST    = "3";
    const std::string BACK               = "0";
}

class PlaylistView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showPlaylistList(const std::vector<Playlist>& playlists);
    void selectPlaylist(const Playlist& playlist);
    void handleInput(const std::string& input) override;
};
#endif // PLAYLIST_VIEW_H
