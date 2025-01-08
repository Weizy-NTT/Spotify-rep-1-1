#include "ScanfOptionView.hpp"
#include <iostream>

void ScanfOptionView::showMenu() {
    std::string scanChoice;
    std::cout << "===== Scanf Option Menu =====\n";
    std::cout << ScanfMenu::SCANF_DIRECTORY << ". Scan Directory\n";
    std::cout << ScanfMenu::SCANF_USB << ". Scan USB Device\n";
    std::cout << ScanfMenu::BACK << ". Go Back\n";
    std::cout << "=============================\n";
}

void ScanfOptionView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Scanf Option View...\n";
    std::system("clear");
}

