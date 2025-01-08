#include "PlaylistView.hpp"
#include <iostream>

void PlaylistView::showMenu() {
    BaseView::showMenu();
    std::string playlistChoice;

    std::cout << "===== Playlist Menu =====\n";
    std::cout << PlaylistMenu::SELECT_PLAYLIST << ". Select a Playlist\n";
    std::cout << PlaylistMenu::ADD_PLAYLIST << ". Add a Playlist\n";
    std::cout << PlaylistMenu::REMOVE_PLAYLIST << ". Remove a Playlist\n";
    std::cout << PlaylistMenu::BACK << ". Go Back\n";
    std::cout << "=========================\n";

    do {
        std::cout << "Enter your choice: ";
        std::getline(std::cin, playlistChoice);
    } while (playlistChoice != PlaylistMenu::SELECT_PLAYLIST &&
             playlistChoice != PlaylistMenu::ADD_PLAYLIST &&
             playlistChoice != PlaylistMenu::REMOVE_PLAYLIST &&
             playlistChoice != PlaylistMenu::BACK);
    PlaylistView::handleInput(playlistChoice);
}

void PlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Media File View...\n";
}

void PlaylistView::showPlaylistList(const std::vector<Playlist>& playlists) {
    std::cout << "===== Playlist List =====\n";
    for (size_t i = 0; i < playlists.size(); ++i) {
        std::cout << i + 1 << ". " << playlists[i].getName() << std::endl;
    }
    std::cout << "=========================\n";
}

void PlaylistView::selectPlaylist(const Playlist& playlist) {
    std::cout << "You selected the playlist: " << playlist.getName() << std::endl;
    // di chuyen den detailedplaylist view
}

void PlaylistView::handleInput(const std::string& input) {
    if (input == PlaylistMenu::SELECT_PLAYLIST) {
        std::cout << "Displaying the playlist list...\n";
        // di chuyen den detailedplaylist view
    } else if (input == PlaylistMenu::ADD_PLAYLIST) {
        std::cout << "Please enter the name of the new playlist...\n";
        // Chức năng thêm playlist có thể được gọi ở đây
    } else if (input == PlaylistMenu::REMOVE_PLAYLIST) {
        std::cout << "Please select a playlist to remove...\n";
        // Chức năng xóa playlist có thể được gọi ở đây
    } else if (input == PlaylistMenu::BACK) {
        std::cout << "Going back to the previous menu...\n";
        // Chức năng quay lại menu trước có thể được gọi ở đây
    } else {
        std::cout << "Invalid option. Please try again.\n";
    }
}

