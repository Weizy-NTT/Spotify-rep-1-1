#ifndef PLAYLIST_CONTROLLER_H
#define PLAYLIST_CONTROLLER_H

#include <vector>
#include "Playlist.hpp"
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "ControllerManager.hpp"
#include "ModelManager.hpp"

class PlaylistController : public BaseController {
public:
    void inputFromKeyboard();
    void handleInput(const size_t & input);
    std::vector<Playlist> getAllPlaylists() const;
    void createPlaylist(const std::string& name);
    void back();
    void deletePlaylist(const std::string& name);
    void showMediafileInList(const std::string& listId);
};


#endif // PLAYLIST_CONTROLLER_
