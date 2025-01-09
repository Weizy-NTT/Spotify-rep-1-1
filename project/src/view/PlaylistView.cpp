#include "PlaylistView.hpp"
#include <iostream>

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
    std::cout << "===== Playlist List =====\n";
    for (size_t i = 0; i < playlists.size(); ++i) {
        std::cout << i + 1 << ". " << playlists[i]->getName() << std::endl;
    }
    std::cout << "=========================\n";
}


