#ifndef PLAYLIST_CONTROLLER_H
#define PLAYLIST_CONTROLLER_H

#include <vector>
#include "Playlist.hpp"
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "ControllerManager.hpp"
#include "ModelManager.hpp"
#include "ViewManager.hpp"

class PlaylistController : public BaseController {
public:
    void handleInput();
    void createPlaylist(const std::string& name, const std::string Id);
    void back();
    void deletePlaylist(const std::string& Id);
    void showMediafileInList(const std::string& listId);
};


#endif // PLAYLIST_CONTROLLER
