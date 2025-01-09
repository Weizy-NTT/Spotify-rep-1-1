#include "PlaylistLibrary.hpp"
#include <algorithm>
#include <stdexcept>

std::vector<Playlist> PlaylistLibrary::getAllPlaylists() const {
    return playlists;
}

void PlaylistLibrary::addPlaylist(const Playlist& playlist) {
    playlists.push_back(playlist);
}

void PlaylistLibrary::removePlaylist(const Playlist& playlist) {
    for (auto it = playlists.begin();it != playlists.end();it++) {
        if (it->getName() == playlist.getName()) {
            playlists.erase(it);
            return;
        }
    }
}

Playlist PlaylistLibrary::getPlaylistByName(const std::string& name) const {
    for (const auto& playlist : playlists) {
        if (playlist.getName() == name) {
            return playlist;
        }
    }
    throw std::runtime_error("Playlist not found");
}
