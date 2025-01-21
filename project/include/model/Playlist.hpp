#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "MediaFile.hpp"
#include <memory>
#include <queue>

class Playlist {
private:
    static size_t playlistNextID;                  // Static variable to track the next unique ID for playlists
    std::string ID;                                // Unique identifier for the playlist
    std::string name;                              // Name of the playlist
    std::vector<std::shared_ptr<MediaFile>> songs; // List of songs in the playlist

public:
    // Constructor to initialize a playlist with a given name
    Playlist(const std::string& name);

    // Get the unique ID of the playlist
    std::string getID() const;

    // Get the name of the playlist
    std::string getName() const;
    void setID(const std::string& ID);
    const std::vector<std::shared_ptr<MediaFile>>& getSongs() const;

    // Add a song to the playlist
    void addSong(const std::shared_ptr<MediaFile>& song);

    // Remove a song from the playlist by its ID
    void removeSong(const std::string& ID);

    // Check if a media file ID exists in the playlist
    bool isValidMediaFileIDInPlaylist(const std::string& ID);

    // Get a song from the playlist by its ID
    std::shared_ptr<MediaFile> getSongByID(const std::string& ID) const;

    // Destructor for the Playlist class
    ~Playlist();
};

#endif // PLAYLIST_H
