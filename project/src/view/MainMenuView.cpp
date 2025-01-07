#include "MainMenuView.hpp"
#include <iostream>
#include "ViewManager.hpp"

void MainMenuView::showMenu() {
    BaseView::showMenu();
    std::cout << "Welcome to the Media Player!" << std::endl;
    std::cout << "1. Scan" << std::endl;
    std::cout << "2. All Songs" << std::endl;
    std::cout << "3. Playlist" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Please select an option: ";
}

void MainMenuView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Main Menu..." << std::endl;
}

void MainMenuView::handleInput(const std::string& input) {
    if (input == SCAN_OPTIONS) {
        // Chuyển tới ViewScanfOption
        MainMenuView::hideMenu();
        ViewManager::getInstance().switchView(std::make_unique<ScanfOptionView>());
        std::cout << "You selected Scan." << std::endl;
    }
    else if (input == ALL_SONGS) {
        // Chuyển tới ViewMediaFiles
        std::cout << "You selected All Songs." << std::endl;
    }
    else if (input == PLAYLIST) {
        // Chuyển tới ViewPlaylist
        std::cout << "You selected Playlist." << std::endl;
    }
    else if (input == EXIT) {
        std::cout << "Exiting the program." << std::endl;
        std::exit(0);
    }
    else {
        std::cout << "Invalid input. Please try again." << std::endl;
    }
}
