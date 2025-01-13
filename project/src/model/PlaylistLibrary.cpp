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

void PlaylistLibrary::loadFromFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        std::cerr << "Failed to open file for reading: " << filePath << "\n";
        return;
    }

    std::string line;
    std::shared_ptr<Playlist> currentPlaylist = nullptr;

    while (std::getline(inFile, line)) {
        // Xóa khoảng trắng
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            continue;
        }

        // Nếu dòng không chứa đường dẫn (tức là tên playlist)
        if (line.find("/") == std::string::npos) {
            if (currentPlaylist) {
                playlists.push_back(currentPlaylist);
            }

            currentPlaylist = std::make_shared<Playlist>(line); // Tạo playlist mới với tên
        } else {
            // Thêm bài hát vào playlist hiện tại
            if (currentPlaylist) {
                auto new_mediafile = std::make_shared<MediaFile>();
                new_mediafile->setPath(line);
                new_mediafile->setName(fs::path(line).filename().string());
                currentPlaylist->addSong(new_mediafile);
            }
        }
    }

    if (currentPlaylist) {
        playlists.push_back(currentPlaylist);
    }

    inFile.close();
    std::cout << "Playlists loaded from " << filePath << "\n";
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

        // Ghi các bài hát
        for (const auto& song : playlist->getSongs()) {
            outFile << song->getPath() << "\n";
        }

        // Ngăn cách các playlist
        outFile << "\n";
    }

    outFile.close();
    std::cout << "Playlists saved to " << filePath << "\n";
}
