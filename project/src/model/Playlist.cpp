#include "Playlist.hpp"
#include <algorithm>

size_t Playlist::playlistNextID = 1;
std::queue<int> Playlist::playlistFreeIDs;

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

bool Playlist::isValidMediaFileIDInPlaylist(const std::string& ID) {
    for (const auto& song : songs) {
        if (song->getID() == ID) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<MediaFile> Playlist::getSongByID(const std::string& ID) const {
    for (const auto& song : songs) {
        if (song->getID() == ID) {
            return song;
        }
    }
    return nullptr;
}

std::string Playlist::getID() const {
    return ID;
}

Playlist::Playlist(const std::string& name) {
    if (!playlistFreeIDs.empty()) {
        ID = std::to_string(playlistFreeIDs.front());
        playlistFreeIDs.pop();
    } else {
        ID = std::to_string(playlistNextID++);
    }
    this->name = name;
}

Playlist::~Playlist() {
    playlistFreeIDs.push(std::stoi(ID));
}