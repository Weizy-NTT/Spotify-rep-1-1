#include "ScanfOptionView.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // Để dùng text, vbox, border
#include <iostream>
using namespace ftxui;

void ScanfOptionView::showMenu() {
    // Tạo menu
    auto menu = Menu(&menu_entries, &selected_option);

    // Tạo renderer để hiển thị menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Scanf Option Menu ====="),
                   menu->Render(),
                   text("============================="),
                   text("Use arrow keys or mouse to navigate, press Enter or click to select."),
               }) |
               border;
    });

    // Tạo đối tượng ScreenInteractive
    auto screen = ScreenInteractive::TerminalOutput();

    // Xử lý sự kiện
    auto event_handler = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left && menu->OnEvent(event)) {
                screen.ExitLoopClosure()(); // Thoát vòng lặp khi click vào menu
                return true;
            }
        }
        if (event == Event::Return) {
            if (menu->OnEvent(event)) {
            screen.ExitLoopClosure()();
            return true;
            }
        } 
        if (event == Event::Escape || event == Event::Character('q')) {
            screen.ExitLoopClosure()(); // Thoát vòng lặp khi nhấn ESC hoặc 'q'
            return true;
        }
        return menu->OnEvent(event);
    });

    // Chạy vòng lặp giao diện
    screen.Loop(event_handler);
    std::system("clear");
}

int ScanfOptionView::getSelectedOption() const {
    return selected_option;
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


