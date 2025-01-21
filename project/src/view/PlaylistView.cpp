#include "PlaylistView.hpp"
#include <iostream>
#include <iomanip>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

void PlaylistView::showMenu() {
    BaseView::showMenu();
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
    //std::system("clear");
}

int PlaylistView::getSelectedOption() const {
    return selected_option;
}


void PlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::system("clear");
}

void PlaylistView::showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists) {
    using namespace ftxui;

    // 1. Tạo danh sách playlist
    Elements items;
    for (const auto& playlist : playlists) {
        items.push_back(hbox({
            text("[" + playlist->getID() + "] ") | size(WIDTH, EQUAL, 10),   // Cột ID
            text(playlist->getName()) | size(WIDTH, GREATER_THAN, 30)       // Cột Name
        }));
    }

    // 2. Tạo tiêu đề
    auto header = text("============= Playlist List =============") | bold | hcenter;

    // 3. Tạo footer
    auto footer = text("Total Playlists: " + std::to_string(playlists.size())) | hcenter;

    // 4. Kết hợp giao diện
    auto document = vbox({
        header,
        separator(),
        vbox(std::move(items)) | border, // Hiển thị danh sách
        separator(),
        footer
    });

    // 5. Điều chỉnh màn hình
    auto screen = Screen::Create(
        Dimension::Full(),         // Chiều rộng tự động chiếm hết
        Dimension::Fit(document)   // Chiều cao tự động vừa nội dung
    );
    Render(screen, document);

    // 6. Hiển thị giao diện
    std::cout << screen.ToString() << std::endl;

    
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



