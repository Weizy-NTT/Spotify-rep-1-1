#include "MainMenuView.hpp"
#include <iostream>
#include "ViewManager.hpp"

void MainMenuView::showMenu() {
    BaseView::showMenu();

    constexpr int MENU_WIDTH = 66; // Chiều rộng của menu, khớp với DetailedPlaylistMenu

    // Hàm vẽ đường viền trên/dưới
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Main Menu";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị các tùy chọn menu
    std::cout << "| " << MainMenu::SCAN_OPTIONS << ". Scan" << std::string(MENU_WIDTH - 8, ' ') << "|\n";
    std::cout << "| " << MainMenu::ALL_SONGS << ". All Songs" << std::string(MENU_WIDTH - 13, ' ') << "|\n";
    std::cout << "| " << MainMenu::PLAYLIST << ". Playlist" << std::string(MENU_WIDTH - 12, ' ') << "|\n";
    std::cout << "| " << MainMenu::NOW_PLAYING << ". Now Playing" << std::string(MENU_WIDTH - 15, ' ') << "|\n";
    std::cout << "| " << MainMenu::EXIT << ". Exit" << std::string(MENU_WIDTH - 8, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}

void MainMenuView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Main Menu..." << std::endl;
    std::system("clear");
}

