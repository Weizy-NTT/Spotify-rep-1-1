#include "MediaFileView.hpp"
#include <iostream>
#include <iomanip>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // Để dùng text, vbox, border

using namespace ftxui;

void MediaFileView::showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, size_t currentPage, size_t firstSong, size_t lastSong) {
    constexpr int ID_WIDTH = 5;       // Width for ID column
    constexpr int NAME_WIDTH = 30;   // Width for Name column

    // Display page header
    std::cout << "----------------------------------------\n";
    std::cout << "              Page " << currentPage << "\n";
    std::cout << "----------------------------------------\n";

    // Display table header
    std::cout << std::left << std::setw(ID_WIDTH) << "ID" 
              << std::left << std::setw(NAME_WIDTH) << "Name" << "\n";
    std::cout << "----------------------------------------\n";

    // Display media file rows
    for (size_t i = firstSong; i <= lastSong; ++i) {
        if (i < files.size()) {
            std::cout << std::left << std::setw(ID_WIDTH) << files[i]->getID()
                      << std::left << std::setw(NAME_WIDTH) << files[i]->getName() << "\n";
        }
    }

    // Footer
    std::cout << "----------------------------------------\n";
}

void MediaFileView::showMenu() {
    // Tạo menu với các mục
    auto menu = Menu(&menu_entries, &selected_option);

    // Tạo renderer để hiển thị menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("==== Media Player Menu ===="),
                   menu->Render(),
                   text("==========================="),
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

int MediaFileView::getSelectedOption() const {
    return selected_option;
}

void MediaFileView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Media File View...\n";
    std::system("clear");
}

void MediaFileView::displayStatusMessage(MediaFileStatus& status) {
    switch (status) {
        case MediaFileStatus::MEDIAFILE_PLAY_STATUS:
            std::cout << "Song ID not found in media library. Cannot play.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset lại trạng thái
            break;
        case MediaFileStatus::MEDIAFILE_DETAIL_STATUS:
            std::cout << "Song ID not found in media library. Cannot show details.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset lại trạng thái
            break;
        case MediaFileStatus::MEDIAFILE_NEXT_PAGE_STATUS:
            std::cout << "This is the last page. Cannot go next.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset lại trạng thái
            break;
        case MediaFileStatus::MEDIAFILE_PREV_PAGE_STATUS:
            std::cout << "This is the first page. Cannot go back.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset lại trạng thái
            break;
        case MediaFileStatus::MEDIAFILE_NORMAL:
        default:
            // Không cần thông báo khi ở trạng thái bình thường
            break;
    }
}


