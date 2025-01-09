#include "MediaFileView.hpp"
#include <iostream>

void MediaFileView::showMediaFilesPage(const std::vector<MediaFile>& files, int currentPage, int firstSong, int lastSong) {
    std::cout << "Showing page " << currentPage << std::endl;
    for (int i = firstSong; i < lastSong + 1; i++) {
        std::cout << i + 1 << ". " << files[i].getName();
    }
}

void MediaFileView::showMenu() {
    BaseView::showMenu();
    std::cout << "==== Media Player Menu ====" << std::endl;
    std::cout << MediaFileMenu::PLAY_SONG << ". Play\n";
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

