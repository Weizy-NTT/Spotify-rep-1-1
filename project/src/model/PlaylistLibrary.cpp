#include "PlaylistLibrary.hpp"
#include <algorithm>
#include <filesystem>

// Returns a reference to the list of all playlists.
const std::vector<std::shared_ptr<Playlist>>& PlaylistLibrary::getAllPlaylists() const {
    return playlists; // Provides access to all playlists managed by the library.
}

// Adds a new playlist to the library.
void PlaylistLibrary::addPlaylist(const std::shared_ptr<Playlist>& playlist) {
    playlists.push_back(playlist); // Appends the playlist to the list.
}

// Removes a playlist from the library by its ID.
void PlaylistLibrary::removePlaylist(const std::string& ID) {
    // Find and remove the playlist with the specified ID.
    auto it = std::remove_if(playlists.begin(), playlists.end(),
        [&ID](const std::shared_ptr<Playlist>& playlist) {
            return playlist->getID() == ID; // Check if the playlist's ID matches.
        });

    // If a playlist was removed, erase it from the list.
    if (it != playlists.end()) {
        playlists.erase(it, playlists.end());
    }

    // Adjust the IDs of the remaining playlists to ensure sequential IDs.
    for (size_t i = std::stoi(ID) - 1; i < playlists.size(); i++) {
        playlists[i]->setID(std::to_string(i + 1));
    }
}

// Retrieves a playlist by its ID.
std::shared_ptr<Playlist> PlaylistLibrary::getPlaylistByID(const std::string& ID) const {
    // Iterate through all playlists to find the one with the matching ID.
    for (const auto& playlist : playlists) {
        if (playlist->getID() == ID) {
            return playlist; // Return the matching playlist.
        }
    }
    return nullptr; // Return nullptr if no matching playlist is found.
}

// Checks if a playlist with the given ID exists in the library.
bool PlaylistLibrary::isValidPlaylistIDInLibrary(const std::string& ID) {
    // Iterate through playlists to see if any match the given ID.
    for (const auto& playlist : playlists) {
        if (playlist->getID() == ID) {
            return true; // ID is valid if found in the library.
        }
    }
    return false; // Return false if no match is found.
}

// Saves all playlists to a file.
void PlaylistLibrary::saveToFile(const std::string& filePath) const {
    std::ofstream outFile(filePath, std::ios::out); // Open the file for writing.
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filePath << "\n"; // Handle file open errors.
        return;
    }

    // Iterate through each playlist in the library.
    for (const auto& playlist : playlists) {
        // Write the playlist name to the file.
        outFile << playlist->getName() << "\n";

        // Write each song's path in the playlist.
        for (const auto& song : playlist->getSongs()) {
            outFile << song->getPath() << "\n";
        }

        // Add an empty line to separate playlists.
        outFile << "\n";
    }

    outFile.close(); // Close the file after writing.
    std::cout << "Playlists saved to " << filePath << "\n"; // Confirm save success.
}
