#ifndef DETAILED_PLAYLIST_VIEW_H
#define DETAILED_PLAYLIST_VIEW_H

#include "BaseView.hpp"
#include "Playlist.hpp"
#include <iostream>
#include <vector>

enum DetailedPlaylistMenu {
    BACK_FROM_DETAIL,
    SHOW_DETAILS,
    SHOW_SONGS
};

class DetailedPlaylistView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showPlaylistDetails(const Playlist& playlist);
    void showListOfSongs(const Playlist& playlist);
};

#endif // DETAILED_PLAYLIST_VIEW_H
