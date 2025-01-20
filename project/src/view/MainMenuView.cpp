#include "MainMenuView.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // Để dùng text, vbox, border
#include <iostream>
using namespace ftxui;

void MainMenuView::showMenu() {;
    // Tạo menu với các mục đã khai báo
    auto menu = Menu(&menu_entries, &selected_option);

    // Tạo renderer để hiển thị menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Main Menu ====="),
                   menu->Render(),
                   text("====================="),
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

int MainMenuView::getSelectedOption() const {
    return selected_option;
}

void MainMenuView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Main Menu..." << std::endl;
    std::system("clear");
}

