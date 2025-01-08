#ifndef PLAYLIST_CONTROLLER_H
#define PLAYLIST_CONTROLLER_H

#include <vector>
#include "Playlist.hpp"
#include "BaseController.hpp"

class PlaylistController : public BaseController {
public:
    void inputFromKeyboard();
    void handleInput(const std::string& input);
    std::vector<Playlist> getAllPlaylists() const;
    void createPlaylist(const std::string& name);
    void deletePlaylist(const std::string& name);
};

#endif // PLAYLIST_CONTROLLER_H
