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
    std::cout << "Playlist Details:\n";
    std::cout << "Name: " << playlist->getName() << "\n";
    std::cout << "Number of Songs: " << playlist->getSongs().size() << "\n";
}

void DetailedPlaylistView::showListOfSongs(const std::shared_ptr<Playlist>& playlist) {
    constexpr int ID_WIDTH = 5;       // Width for ID column
    constexpr int NAME_WIDTH = 30;   // Width for Name column

    // Display header with playlist name
    std::cout << "----------------------------------------\n";
    std::cout << "    Songs in Playlist: " << playlist->getName() << "\n";
    std::cout << "----------------------------------------\n";

    // Display table header
    std::cout << std::left << std::setw(ID_WIDTH) << "ID"
              << std::left << std::setw(NAME_WIDTH) << "Name" << "\n";
    std::cout << "----------------------------------------\n";

    // Fetch and display songs in the playlist
    std::vector<std::shared_ptr<MediaFile>> songs = playlist->getSongs();
    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << std::left << std::setw(ID_WIDTH) << songs[i]->getID()
                  << std::left << std::setw(NAME_WIDTH) << songs[i]->getName() << "\n";
    }

    // Footer
    std::cout << "----------------------------------------\n";
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
