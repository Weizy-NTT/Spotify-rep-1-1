#include "MainMenuView.hpp"
#include <iostream>
#include "ViewManager.hpp"

void MainMenuView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Main Menu =====" << std::endl;
    std::cout << MainMenu::SCAN_OPTIONS << ". Scan\n";
    std::cout << MainMenu::ALL_SONGS << ". All Songs\n";
    std::cout << MainMenu::PLAYLIST << ". Playlist\n";
    std::cout << MainMenu::EXIT << ". Exit\n";
    std::cout << "=====================" << std::endl;
}

void MainMenuView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Main Menu..." << std::endl;
    std::system("clear");
}

