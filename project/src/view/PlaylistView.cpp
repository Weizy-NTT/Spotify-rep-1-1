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

// void PlaylistView::showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists) {
//     std::cout << "===== Playlist List =====\n";
//     for (size_t i = 0; i < playlists.size(); ++i) {
//         std::cout << i + 1 << ". " << playlists[i]->getName() << std::endl;
//     }
//     std::cout << "=========================\n";
// }

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



