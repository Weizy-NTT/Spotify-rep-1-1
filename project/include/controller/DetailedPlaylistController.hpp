#ifndef DETAILED_PLAYLIST_CONTROLLER_H
#define DETAILED_PLAYLIST_CONTROLLER_H

#include "Playlist.hpp"
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "ControllerManager.hpp"

class DetailedPlaylistController : public BaseController {
public:
    void handleInput(std::string listId);
    void showDetailSong(const std::string& PlaylistId, const std::string& songID);
    void addSongToPlaylist(const std::string& PlaylistId, const std::string& songID);
    void removeSongFromPlaylist(const std::string& PlaylistId, const std::string& songID);
    void back();
    void playSong(const std::string songID);
};

#endif // DETAILED_PLAYLIST_CONTROLLER
