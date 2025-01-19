#ifndef DETAILED_PLAYLIST_VIEW_H
#define DETAILED_PLAYLIST_VIEW_H

#include "BaseView.hpp"
#include "Playlist.hpp"
#include <iostream>
#include <vector>
#include <memory>

enum DetailedPlaylistMenu {
    BACK_FROM_DETAIL,
    PLAY_SONG_FROM_PLAYLIST,
    ADD_SONG,
    DELETE_SONG,
    SHOW_DETAIL_SONG
};

enum DetailedPlaylistStatus {
    DETAILED_NORMAL,
    DETAILED_ADD_STATUS,
    DETAILED_PLAY_STATUS,
    DETAILED_DELETE_STATUS,
    DETAILED_SHOW_STATUS,
};

class DetailedPlaylistView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showListOfSongs(const std::shared_ptr<Playlist>& playlist);
    void displayStatusMessage(DetailedPlaylistStatus& status);
};

#endif // DETAILED_PLAYLIST_VIEW_H
