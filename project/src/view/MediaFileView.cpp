#include "MediaFileView.hpp"
#include <iostream>

void MediaFileView::showMediaFilesPage(const std::vector<MediaFile>& files, int currentPage) {

}

void MediaFileView::showMenu() {
    BaseView::showMenu();
    std::cout << "\n--- Media Player Menu ---" << std::endl;
    std::cout << MediaFileMenu::PLAY << ". Play\n";
    std::cout << MediaFileMenu::SHOW_DETAIL << ". Show Media File Details\n";
    std::cout << MediaFileMenu::NEXT_PAGE << ". Show Next Page\n";
    std::cout << MediaFileMenu::PREV_PAGE << ". Show Previous Page\n";
    std::cout << MediaFileMenu::BACK << ". Go Back\n";
    std::cout << "===========================" << std::endl;
}

void MediaFileView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Media File View...\n";
    std::system("clear");
}

