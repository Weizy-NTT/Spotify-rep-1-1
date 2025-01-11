#include "ScanfOptionView.hpp"
#include <iostream>

void ScanfOptionView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Scanf Option Menu =====" << std::endl;
    std::cout << ScanfMenu::SCANF_DIRECTORY << ". Scan Directory\n";
    std::cout << ScanfMenu::SCANF_USB << ". Scan USB Device\n";
    std::cout << ScanfMenu::BACK_FROM_SCAN << ". Go Back\n";
    std::cout << "=============================" << std::endl;
}

void ScanfOptionView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Scanf Option View...\n";
    std::system("clear");
}

