#include "ScanfOptionView.hpp"
#include <iostream>

void ScanfOptionView::showMenu() {
    BaseView::showMenu();

    constexpr int MENU_WIDTH = 66; // Chiều rộng của menu, đồng bộ với các menu khác

    // Hàm vẽ đường viền trên/dưới
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Scanf Option Menu";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị các tùy chọn menu
    std::cout << "| " << ScanfMenu::SCANF_DIRECTORY << ". Scan Directory" 
              << std::string(MENU_WIDTH - 18, ' ') << "|\n";
    std::cout << "| " << ScanfMenu::SCANF_USB << ". Scan USB Device" 
              << std::string(MENU_WIDTH - 19, ' ') << "|\n";
    std::cout << "| " << ScanfMenu::BACK_FROM_SCAN << ". Go Back" 
              << std::string(MENU_WIDTH - 11, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}

void ScanfOptionView::hideMenu() {
    BaseView::hideMenu();
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


