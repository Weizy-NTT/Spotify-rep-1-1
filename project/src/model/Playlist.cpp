#include "Playlist.hpp"
#include <algorithm>
#include <stdexcept>

std::string Playlist::getName() const {
    return name;
}

std::vector<MediaFile> Playlist::getSongs() const {
    return songs;
}

void Playlist::addSong(const MediaFile& song) {
    songs.push_back(song);
}

void Playlist::removeSong(const MediaFile& song) {
    for (auto it = songs.begin();it != songs.end();it++) {
        if (it->getName() == song.getName()) {
            songs.erase(it);
            return;
        }
    }
}

MediaFile Playlist::getSongByName(const std::string& nameSong) {
    for (const auto& song : songs) {
        if (song.getName() == nameSong) {
            return song;
        }
    }
    throw std::runtime_error("Playlist not found");
}
