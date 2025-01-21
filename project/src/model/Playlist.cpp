#include "Playlist.hpp"
#include <algorithm>

// Initialize static members for unique playlist IDs
size_t Playlist::playlistNextID = 1;

// Get the name of the playlist
std::string Playlist::getName() const {
    return name;
}

// Get all songs in the playlist
const std::vector<std::shared_ptr<MediaFile>>& Playlist::getSongs() const {
    return songs;
}

// Add a song to the playlist
void Playlist::addSong(const std::shared_ptr<MediaFile>& song) {
    songs.push_back(song);
}

// Remove a song from the playlist by its ID
void Playlist::removeSong(const std::string& ID) {
    auto it = std::remove_if(songs.begin(), songs.end(),
        [&ID](const std::shared_ptr<MediaFile>& song) {
            return song->getID() == ID; // Remove the song if the ID matches
        });

    if (it != songs.end()) {
        songs.erase(it, songs.end()); // Erase the matching song(s)
    }
}

// Check if a song with the given ID exists in the playlist
bool Playlist::isValidMediaFileIDInPlaylist(const std::string& ID) {
    for (const auto& song : songs) {
        if (song->getID() == ID) {
            return true; // Return true if a matching song is found
        }
    }
    return false; // Return false if no match is found
}

// Retrieve a song from the playlist by its ID
std::shared_ptr<MediaFile> Playlist::getSongByID(const std::string& ID) const {
    for (const auto& song : songs) {
        if (song->getID() == ID) {
            return song; // Return the matching song
        }
    }
    return nullptr; // Return nullptr if no match is found
}

// Get the unique ID of the playlist
std::string Playlist::getID() const {
    return ID;
}

void Playlist::setID(const std::string& ID) {
    this->ID = ID;
}

Playlist::Playlist(const std::string& name) {
    ID = std::to_string(playlistNextID++);
    this->name = name;
}

Playlist::~Playlist() {
    playlistNextID--;
}