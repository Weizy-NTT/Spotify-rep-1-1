#include "Playlist.hpp"
#include <algorithm>

std::string Playlist::getName() const {
    return name;
}

const std::vector<std::shared_ptr<MediaFile>>& Playlist::getSongs() const {
    return songs;
}

void Playlist::addSong(const std::shared_ptr<MediaFile>& song) {
    songs.push_back(song);
}

void Playlist::removeSong(const std::string& ID) {
    auto it = std::remove_if(songs.begin(), songs.end(),
        [&ID](const std::shared_ptr<MediaFile>& song) {
            return song->getID() == ID;
        });

    if (it != songs.end()) {
        songs.erase(it, songs.end());
    }
}

std::shared_ptr<MediaFile> Playlist::getSongByID(const std::string& ID) const {
    for (const auto& song : songs) {
        if (song->getID() == ID) {
            return song;
        }
    }
    return nullptr;
}

void Playlist::setID(const std::string& ID) {
    this->ID = ID;
}

std::string Playlist::getID() const {
    return ID;
}

Playlist::Playlist(std::string id, std::string name){
    ID = id;
    name = name;
}