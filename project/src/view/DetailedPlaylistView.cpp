#include "DetailedPlaylistView.hpp"

void DetailedPlaylistView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Detailed Playlist Menu =====" << std::endl;
    std::cout << DetailedPlaylistMenu::SHOW_DETAILS << ". Show Playlist Details\n";
    std::cout << DetailedPlaylistMenu::SHOW_SONGS << ". Show List of Songs\n";
    std::cout << DetailedPlaylistMenu::BACK_FROM_DETAIL << ". Go Back\n";
    std::cout << "===============================" << std::endl;
}

void DetailedPlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Detailed Playlist View...\n";
    std::system("cls");
}

void DetailedPlaylistView::showPlaylistDetails(const Playlist& playlist) {
    std::cout << "Playlist Details:\n";
    std::cout << "Name: " << playlist.getName() << "\n";
    std::cout << "Number of Songs: " << playlist.getSongs().size() << "\n";
}

void DetailedPlaylistView::showListOfSongs(const Playlist& playlist) {
    std::cout << "Songs in Playlist:\n";
    std::vector<MediaFile> songs = playlist.getSongs();
    for (const auto& song : songs) {
        std::cout << song.getName() << "\n";
    }
}
