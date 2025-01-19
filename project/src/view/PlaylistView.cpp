#include "PlaylistView.hpp"
#include <iostream>
#include <iomanip>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

void PlaylistView::showMenu() {
    // Tạo menu
    auto menu = Menu(&menu_entries, &selected_option);

    // Tạo renderer để hiển thị menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Playlist Menu ====="),
                   menu->Render(),
                   text("========================="),
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

int PlaylistView::getSelectedOption() const {
    return selected_option;
}


void PlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Media File View...\n";
    std::system("clear");
}

void PlaylistView::showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists) {
    constexpr int ID_WIDTH = 5;       // Width for ID column
    constexpr int NAME_WIDTH = 30;   // Width for Name column

    // Display header
    std::cout << "----------------------------------------\n";
    std::cout << "             Playlist List\n";
    std::cout << "----------------------------------------\n";

    // Display table header
    std::cout << std::left << std::setw(ID_WIDTH) << "ID"
              << std::left << std::setw(NAME_WIDTH) << "Name" << "\n";
    std::cout << "----------------------------------------\n";

    // Display playlist rows
    for (size_t i = 0; i < playlists.size(); ++i) {
        std::cout << std::left << std::setw(ID_WIDTH) << playlists[i]->getID()
                  << std::left << std::setw(NAME_WIDTH) << playlists[i]->getName() << "\n";
    }

    // Footer
    std::cout << "----------------------------------------\n";
}

void PlaylistView::displayStatusMessage(PlaylistStatus& status) {
    switch (status) {
        case PlaylistStatus::PLAYLIST_SELECT_STATUS:
            std::cout << "Error: The playlist ID was not found in the library.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_ADD_STATUS:
            std::cout << "Error: Could not add playlist. Please try again.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_REMOVE_STATUS:
            std::cout << "Error: The playlist ID was not found in the library. Could not remove.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_NORMAL:
        default:
            // Không cần thông báo khi ở trạng thái bình thường
            break;
    }
}



