#ifndef PLAYLIST_CONTROLLER_H
#define PLAYLIST_CONTROLLER_H

#include <vector>
#include "Playlist.hpp"

class PlaylistController {
public:
    std::vector<Playlist> getAllPlaylists() const;
    void createPlaylist(const std::string& name);
    void deletePlaylist(const std::string& name);
};

#endif // PLAYLIST_CONTROLLER_H
