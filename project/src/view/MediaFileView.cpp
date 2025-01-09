#include "MediaFileView.hpp"
#include <iostream>

void MediaFileView::showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, int currentPage, int firstSong, int lastSong) {
    std::cout << "Displaying page " << currentPage << ":\n";
    for (size_t i = firstSong; i <= lastSong; ++i) {
        if (i < files.size()) {
            std::cout << files[i]->getName() << "\n";
        }
    }
}

void MediaFileView::showMenu() {
    BaseView::showMenu();
    std::cout << "==== Media Player Menu ====" << std::endl;
    std::cout << MediaFileMenu::PLAY_SONG_FROM_FILES << ". Play\n";
    std::cout << MediaFileMenu::SHOW_DETAIL << ". Show Media File Details\n";
    std::cout << MediaFileMenu::NEXT_PAGE << ". Show Next Page\n";
    std::cout << MediaFileMenu::PREV_PAGE << ". Show Previous Page\n";
    std::cout << MediaFileMenu::BACK_FROM_MEDIA << ". Go Back\n";
    std::cout << "===========================" << std::endl;
}

void MediaFileView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Media File View...\n";
    std::system("clear");
}

