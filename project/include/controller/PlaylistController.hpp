#ifndef PLAYLIST_CONTROLLER_H
#define PLAYLIST_CONTROLLER_H

#include <vector>
#include "Playlist.hpp"
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include <memory>

class PlaylistController : public BaseController {
public:
    // Handle user input for playlist operations
    void handleInput();

    // Create a new playlist with the specified name
    void createPlaylist(const std::string& name);

    // Navigate back to the previous menu or screen
    void back();

    // Delete a playlist by its ID
    void deletePlaylist(const std::string& Id);

    // Display all playlists from the provided list
    void showAllPlaylists(const std::vector<std::shared_ptr<Playlist>>& lists);
};

#endif // PLAYLIST_CONTROLLER
