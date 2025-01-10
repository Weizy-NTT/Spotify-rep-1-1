#include "MediaFileView.hpp"
#include <iostream>
#include <iomanip>

// void MediaFileView::showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, size_t currentPage, size_t firstSong, size_t lastSong) {
//     std::cout << "Displaying page " << currentPage << ":\n";
//     for (size_t i = firstSong; i <= lastSong; ++i) {
//         if (i < files.size()) {
//             std::cout << files[i]->getID() << " - " << files[i]->getName() << "\n";
//         }
//     }
// }
void MediaFileView::showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, size_t currentPage, size_t firstSong, size_t lastSong) {
    constexpr int ID_WIDTH = 5;       // Width for ID column
    constexpr int NAME_WIDTH = 30;   // Width for Name column

    // Display page header
    std::cout << "----------------------------------------\n";
    std::cout << "              Page " << currentPage << "\n";
    std::cout << "----------------------------------------\n";

    // Display table header
    std::cout << std::left << std::setw(ID_WIDTH) << "ID" 
              << std::left << std::setw(NAME_WIDTH) << "Name" << "\n";
    std::cout << "----------------------------------------\n";

    // Display media file rows
    for (size_t i = firstSong; i <= lastSong; ++i) {
        if (i < files.size()) {
            std::cout << std::left << std::setw(ID_WIDTH) << files[i]->getID()
                      << std::left << std::setw(NAME_WIDTH) << files[i]->getName() << "\n";
        }
    }

    // Footer
    std::cout << "----------------------------------------\n";
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

