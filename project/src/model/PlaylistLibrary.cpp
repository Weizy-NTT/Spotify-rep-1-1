#include "PlaylistLibrary.hpp"
#include <algorithm>

const std::vector<std::shared_ptr<Playlist>>& PlaylistLibrary::getAllPlaylists() const {
    return playlists;
}

void PlaylistLibrary::addPlaylist(const std::shared_ptr<Playlist>& playlist) {
    playlists.push_back(playlist);
}

void PlaylistLibrary::removePlaylist(const std::string& ID) {
    auto it = std::remove_if(playlists.begin(), playlists.end(),
        [&ID](const std::shared_ptr<Playlist>& playlist) {
            return playlist->getName() == ID;
        });

    if (it != playlists.end()) {
        playlists.erase(it, playlists.end());
    }
}

std::shared_ptr<Playlist> PlaylistLibrary::getPlaylistByID(const std::string& ID) const {
    for (const auto& playlist : playlists) {
        if (playlist->getID() == ID) {
            return playlist;
        }
    }
    return nullptr;
}
