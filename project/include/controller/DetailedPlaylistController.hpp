#ifndef DETAILED_PLAYLIST_CONTROLLER_H
#define DETAILED_PLAYLIST_CONTROLLER_H

#include "Playlist.hpp"
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "ControllerManager.hpp"

class DetailedPlaylistController : public BaseController {
public:
    void handleInput(const std::string & ID);
    Playlist getPlaylistDetails(const std::string& playlistName) const;
    void addSongToPlaylist(const std::string& playlistName, const std::string songID);
    void removeSongFromPlaylist(const std::string& playlistName, const std::string songID);
    void back();
    void playSong(const std::string songID);
};
  
#endif // DETAILED_PLAYLIST_CONTROLLER_H
