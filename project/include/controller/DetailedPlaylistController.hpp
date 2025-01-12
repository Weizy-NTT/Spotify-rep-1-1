#ifndef DETAILED_PLAYLIST_CONTROLLER_H
#define DETAILED_PLAYLIST_CONTROLLER_H

#include "Playlist.hpp"
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include <memory>

class DetailedPlaylistController : public BaseController {
public:

    void handleInput(std::string listId);
    void addSongToPlaylist(const std::string& PlaylistId, const std::string& songID);
    void removeSongFromPlaylist(const std::string& PlaylistId, const std::string& songID);
    void back();
    void showMediafileInList(const std::string& listId);
};

#endif // DETAILED_PLAYLIST_CONTROLLER
