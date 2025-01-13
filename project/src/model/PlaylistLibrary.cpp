#include "PlaylistLibrary.hpp"
#include <algorithm>
#include <filesystem>

const std::vector<std::shared_ptr<Playlist>>& PlaylistLibrary::getAllPlaylists() const {
    return playlists;
}

void PlaylistLibrary::addPlaylist(const std::shared_ptr<Playlist>& playlist) {
    playlists.push_back(playlist);
}

void PlaylistLibrary::removePlaylist(const std::string& ID) {
    auto it = std::remove_if(playlists.begin(), playlists.end(),
        [&ID](const std::shared_ptr<Playlist>& playlist) {
            return playlist->getID() == ID;
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

bool PlaylistLibrary::isValidPlaylistIDInLibrary(const std::string& ID) {
    for (const auto& playlist : playlists) {
        if (playlist->getID() == ID) {
            return true;
        }
    }
    return false;
}


void PlaylistLibrary::saveToFile(const std::string& filePath) const {
    std::ofstream outFile(filePath, std::ios::out);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filePath << "\n";
        return;
    }

    for (const auto& playlist : playlists) {
        // Ghi tên playlist
        outFile << playlist->getName() << "\n";

        // Ghi các đường dẫn bài hát
        for (const auto& song : playlist->getSongs()) {
            outFile << song->getPath() << "\n";
        }

        // Ngăn cách các playlist bằng dòng trống
        outFile << "\n";
    }

    outFile.close();
    std::cout << "Playlists saved to " << filePath << "\n";
}
