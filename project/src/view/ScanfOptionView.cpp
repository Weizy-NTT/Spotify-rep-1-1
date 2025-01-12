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

void ScanfOptionView::displayStatusMessage(ScanStatus& status) {
    switch (status) {
        case ScanStatus::SCAN_DIRECTORY_SUCCESS:
            std::cout << "Directory scan successful!\n";
            status = ScanStatus::SCAN_NORMAL;  // Reset trạng thái sau khi thông báo thành công
            break;
        case ScanStatus::SCAN_DIRECTORY_FAILURE:
            std::cout << "Directory scan failed! Please check the path and try again.\n";
            status = ScanStatus::SCAN_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case ScanStatus::SCAN_USB_SUCCESS:
            std::cout << "USB device scan successful!\n";
            status = ScanStatus::SCAN_NORMAL;  // Reset trạng thái sau khi thông báo thành công
            break;
        case ScanStatus::SCAN_USB_FAILURE:
            std::cout << "USB device scan failed! Device not found.\n";
            status = ScanStatus::SCAN_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case ScanStatus::SCAN_NORMAL:
        default:
            // Không cần thông báo khi ở trạng thái bình thường
            break;
    }
}


