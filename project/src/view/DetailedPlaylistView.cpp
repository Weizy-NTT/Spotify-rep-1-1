#include <iomanip>
#include "DetailedPlaylistView.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include "MediaFile.hpp"
#include "Playlist.hpp"

using namespace ftxui;

void DetailedPlaylistView::showMenu() {
    // Tạo menu
    auto menu = Menu(&menu_entries, &selected_option);

    // Tạo renderer để hiển thị menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Detailed Playlist Menu ====="),
                   menu->Render(),
                   text("==============================="),
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

int DetailedPlaylistView::getSelectedOption() const {
    return selected_option;
}

void DetailedPlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Detailed Playlist View...\n";
    std::system("clear");
}

void DetailedPlaylistView::showPlaylistDetails(const std::shared_ptr<Playlist>& playlist) {
    using namespace ftxui;

    // 1. Lấy thông tin chi tiết playlist
    std::string name = playlist->getName();
    size_t numberOfSongs = playlist->getSongs().size();

    // 2. Tạo giao diện hiển thị
    auto document = vbox({
        text("Playlist Details") | bold | hcenter,              // Tiêu đề
        separator(),
        hbox({
            text("Name: ") | bold,                              // Tên playlist
            text(name) | color(Color::Yellow)
        }),
        hbox({
            text("Number of Songs: ") | bold,                   // Số lượng bài hát
            text(std::to_string(numberOfSongs)) | color(Color::Green)
        }),
        separator(),
        text("Press any key to continue...") | dim | hcenter    // Hướng dẫn
    });

    // 3. Điều chỉnh màn hình
    auto screen = Screen::Create(
        Dimension::Full(),         // Chiều rộng tự động chiếm hết
        Dimension::Fit(document)   // Chiều cao tự động vừa nội dung
    );
    Render(screen, document);

    // 4. Hiển thị giao diện
    std::cout << screen.ToString() << std::endl;

}


void DetailedPlaylistView::showListOfSongs(const std::shared_ptr<Playlist>& playlist) {
    using namespace ftxui;

    // 1. Lấy danh sách bài hát
    std::vector<std::shared_ptr<MediaFile>> songs = playlist->getSongs();

    // 2. Tạo danh sách bài hát
    Elements items;
    for (const auto& song : songs) {
        items.push_back(hbox({
            text("[" + song->getID() + "] ") | size(WIDTH, EQUAL, 10),   // Cột ID
            text(song->getName()) | size(WIDTH, GREATER_THAN, 30)       // Cột Tên bài hát
        }));
    }

    // 3. Tạo tiêu đề
    auto header = hbox({
        text("Songs in Playlist: ") | bold,
        text(playlist->getName()) | color(Color::Yellow)
    }) | hcenter;

    // 4. Tạo footer
    auto footer = text("Total Songs: " + std::to_string(songs.size())) | hcenter;

    // 5. Kết hợp giao diện
    auto document = vbox({
        header,
        separator(),
        vbox(std::move(items)) | border, // Hiển thị danh sách
        separator(),
        footer
    });

    // 6. Điều chỉnh màn hình
    auto screen = Screen::Create(
        Dimension::Full(),         // Chiều rộng tự động chiếm hết
        Dimension::Fit(document)   // Chiều cao tự động vừa nội dung
    );
    Render(screen, document);

    // 7. Hiển thị giao diện
    std::cout << screen.ToString() << std::endl;

}

void DetailedPlaylistView::displayStatusMessage(DetailedPlaylistStatus& status) {
    switch (status) {
        case DetailedPlaylistStatus::DETAILED_ADD_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in media library or Song ID exists in playlist. Cannot add.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_PLAY_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot play.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_DELETE_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot delete.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_SHOW_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot show.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_NORMAL:
        default:
            break;
    }
}
