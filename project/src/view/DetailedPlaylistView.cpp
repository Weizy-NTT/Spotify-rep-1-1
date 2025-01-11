#include "DetailedPlaylistView.hpp"
#include <iomanip>

void DetailedPlaylistView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Detailed Playlist Menu =====" << std::endl;
    std::cout << DetailedPlaylistMenu::PLAY_SONG_FROM_PLAYLIST << ". Play a song\n";
    std::cout << DetailedPlaylistMenu::ADD_SONG << ". Add a song to playlist\n";
    std::cout << DetailedPlaylistMenu::DELETE_SONG << ". Delete a song from playlist\n";
    std::cout << DetailedPlaylistMenu::SHOW_DETAIL_SONG << ". Show details of a song\n";
    std::cout << DetailedPlaylistMenu::BACK_FROM_DETAIL << ". Go Back\n";
    std::cout << "===============================" << std::endl;
}

void DetailedPlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Detailed Playlist View...\n";
    std::system("clear");
}

void DetailedPlaylistView::showPlaylistDetails(const std::shared_ptr<Playlist>& playlist) {
    std::cout << "Playlist Details:\n";
    std::cout << "Name: " << playlist->getName() << "\n";
    std::cout << "Number of Songs: " << playlist->getSongs().size() << "\n";
}

void DetailedPlaylistView::showListOfSongs(const std::shared_ptr<Playlist>& playlist) {
    constexpr int ID_WIDTH = 5;       // Width for ID column
    constexpr int NAME_WIDTH = 30;   // Width for Name column

    // Display header with playlist name
    std::cout << "----------------------------------------\n";
    std::cout << "    Songs in Playlist: " << playlist->getName() << "\n";
    std::cout << "----------------------------------------\n";

    // Display table header
    std::cout << std::left << std::setw(ID_WIDTH) << "ID"
              << std::left << std::setw(NAME_WIDTH) << "Name" << "\n";
    std::cout << "----------------------------------------\n";

    // Fetch and display songs in the playlist
    std::vector<std::shared_ptr<MediaFile>> songs = playlist->getSongs();
    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << std::left << std::setw(ID_WIDTH) << songs[i]->getID()
                  << std::left << std::setw(NAME_WIDTH) << songs[i]->getName() << "\n";
    }

    // Footer
    std::cout << "----------------------------------------\n";
}