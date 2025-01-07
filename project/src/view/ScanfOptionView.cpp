#include "ScanfOptionView.hpp"
#include <iostream>

void ScanfOptionView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Scanf Option Menu =====\n";
    std::cout << "1. Scan Directory\n";
    std::cout << "2. Scan USB Device\n";
    std::cout << "0. Go Back\n";
    std::cout << "=============================\n";
}

void ScanfOptionView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Scanf Option View...\n";
}

void ScanfOptionView::handleInput(const std::string& input) {
    if (input == SCANF_DIRECTORY) {
        std::cout << "You chose to scan a directory.\n";
        //đặt hàm call tới controller tại đây
    } else if (input == SCANF_USB) {
        std::cout << "You chose to scan a USB device.\n";
        //đặt hàm call tới controller tại đây
    } else if (input == BACK) {
        std::cout << "Returning to the previous menu...\n";
    } else {
        std::cout << "Invalid input. Please try again.\n";
    }
}
