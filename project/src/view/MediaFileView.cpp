#include "MediaFileView.hpp"
#include <iostream>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>

using namespace ftxui;

void MediaFileView::showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, size_t currentPage, size_t firstSong, size_t lastSong) {
    using namespace ftxui;

    // 1. Tạo danh sách file
    Elements items;
    for (size_t i = firstSong; i <= lastSong && i < files.size(); ++i) {
        items.push_back(hbox({
            text("[" + files[i]->getID() + "] ") | size(WIDTH, EQUAL, 10),
            text(files[i]->getName()) | size(WIDTH, GREATER_THAN, 30)
        }));
    }

    // 2. Tạo footer
    std::string footer = "Page " + std::to_string(currentPage);

    // 3. Xây dựng giao diện
    auto document = vbox({
        text("Media Files") | bold | hcenter,
        separator(),
        vbox(std::move(items)) | border, // Tự động fit với danh sách
        separator(),
        text(footer) | hcenter
    });

    // 4. Điều chỉnh màn hình theo nội dung
    auto screen = Screen::Create(
        Dimension::Full(),         // Chiều rộng tự động chiếm hết
        Dimension::Fit(document)   // Chiều cao tự động vừa nội dung
    );
    Render(screen, document);

    // 5. In giao diện ra terminal
    std::cout << screen.ToString() << std::endl;
}



void MediaFileView::showMenu() {
    BaseView::showMenu();
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

int MediaFileView::getSelectedOption() const {
    return selected_option;
}

void MediaFileView::hideMenu() {
    BaseView::hideMenu();
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


