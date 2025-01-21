#ifndef DETAILED_PLAYLIST_CONTROLLER_H
#define DETAILED_PLAYLIST_CONTROLLER_H

#include "Playlist.hpp"
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include <memory>

class DetailedPlaylistController : public BaseController {
public:
    // Handle user input for a specific playlist
    void handleInput(std::string listId);
    
    // Add a song to the specified playlist
    void addSongToPlaylist(const std::string& PlaylistId, const std::string& songID);
    
    // Remove a song from the specified playlist
    void removeSongFromPlaylist(const std::string& PlaylistId, const std::string& songID);
    
    // Go back to the previous menu or screen
    void back();
    
    // Display all media files in the specified playlist
    void showMediafileInList(const std::string& listId);
};

#endif // DETAILED_PLAYLIST_CONTROLLER

