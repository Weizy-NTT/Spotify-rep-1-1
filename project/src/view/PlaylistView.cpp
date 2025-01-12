#include "PlaylistView.hpp"
#include <iostream>
#include <iomanip>

void PlaylistView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Playlist Menu =====" << std::endl;
    std::cout << PlaylistMenu::SELECT_PLAYLIST << ". Select a Playlist\n";
    std::cout << PlaylistMenu::ADD_PLAYLIST << ". Add a Playlist\n";
    std::cout << PlaylistMenu::REMOVE_PLAYLIST << ". Remove a Playlist\n";
    std::cout << PlaylistMenu::BACK_FROM_PLAYLIST << ". Go Back\n";
    std::cout << "=========================" << std::endl;
}

void PlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Media File View...\n";
    std::system("clear");
}

void PlaylistView::showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists) {
    constexpr int ID_WIDTH = 5;       // Width for ID column
    constexpr int NAME_WIDTH = 30;   // Width for Name column

    // Display header
    std::cout << "----------------------------------------\n";
    std::cout << "             Playlist List\n";
    std::cout << "----------------------------------------\n";

    // Display table header
    std::cout << std::left << std::setw(ID_WIDTH) << "ID"
              << std::left << std::setw(NAME_WIDTH) << "Name" << "\n";
    std::cout << "----------------------------------------\n";

    // Display playlist rows
    for (size_t i = 0; i < playlists.size(); ++i) {
        std::cout << std::left << std::setw(ID_WIDTH) << playlists[i]->getID()
                  << std::left << std::setw(NAME_WIDTH) << playlists[i]->getName() << "\n";
    }

    // Footer
    std::cout << "----------------------------------------\n";
}

void PlaylistView::displayStatusMessage(PlaylistStatus& status) {
    switch (status) {
        case PlaylistStatus::PLAYLIST_SELECT_STATUS:
            std::cout << "Error: The playlist ID was not found in the library.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_ADD_STATUS:
            std::cout << "Error: Could not add playlist. Please try again.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_REMOVE_STATUS:
            std::cout << "Error: The playlist ID was not found in the library. Could not remove.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_NORMAL:
        default:
            // Không cần thông báo khi ở trạng thái bình thường
            break;
    }
}



