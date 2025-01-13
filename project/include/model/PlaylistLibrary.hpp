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
    std::vector<std::shared_ptr<Playlist>> playlists;

public:
    const std::vector<std::shared_ptr<Playlist>>& getAllPlaylists() const;
    void addPlaylist(const std::shared_ptr<Playlist>& playlist);
    void removePlaylist(const std::string& ID);
    std::shared_ptr<Playlist> getPlaylistByID(const std::string& ID) const;
    bool isValidPlaylistIDInLibrary(const std::string& ID);
    void saveToFile(const std::string& filePath) const;
};

#endif // PLAYLISTLIBRARY_H
