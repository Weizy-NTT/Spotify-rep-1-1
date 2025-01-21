#ifndef PLAYLIST_LIBRARY_H
#define PLAYLIST_LIBRARY_H

#include <vector>
#include "Playlist.hpp"
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class PlaylistLibrary {
private:
    std::vector<std::shared_ptr<Playlist>> playlists; // Collection of playlists in the library

public:
    // Get all playlists in the library
    const std::vector<std::shared_ptr<Playlist>>& getAllPlaylists() const;

    // Add a new playlist to the library
    void addPlaylist(const std::shared_ptr<Playlist>& playlist);

    // Remove a playlist from the library by its ID
    void removePlaylist(const std::string& ID);

    // Get a playlist by its unique ID
    std::shared_ptr<Playlist> getPlaylistByID(const std::string& ID) const;

    // Check if a playlist ID exists in the library
    bool isValidPlaylistIDInLibrary(const std::string& ID);

    // Save all playlists in the library to a file
    void saveToFile(const std::string& filePath) const;
};

#endif // PLAYLISTLIBRARY_H
