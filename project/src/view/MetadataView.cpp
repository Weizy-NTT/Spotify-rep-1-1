#include "MetadataView.hpp"
#include <iostream>
#include <iomanip>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // Để dùng text, vbox, border

using namespace ftxui;
void MetadataView::showMenu() {
    // Tạo menu với các mục
    auto menu = Menu(&menu_entries, &selected_option);

    // Tạo renderer để hiển thị menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Metadata Menu ====="),
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
void MetadataView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Metadata View...\n";
    std::system("clear");
}

int MetadataView::getSelectedOption() const {
    return selected_option;
}

void MetadataView::showFileMetadata(const std::shared_ptr<MediaFile>& file) {
    auto metadata = file->getMetadata();

    // Header
    std::cout << "\n+-------------------------------------------------+\n";
    std::cout << "   METADATA OF " << std::setw(20) << file->getName() << "\n";
    std::cout << "+-------------------------------------------------+\n";

    // Content
    for (const auto& entry : metadata.getMetadata()) {
        std::cout << std::left << std::setw(15) << entry.first 
                    << ": " << std::setw(25) << entry.second << "\n";
    }

    // Footer
    std::cout << "+-------------------------------------------------+\n";
}

void MetadataView::menuEditAudio() {
    std::cout << "======================= Audio Edit =======================" << std::endl;
    std::cout << AUDIO_TITLE << ".Title " 
                << AUDIO_ARTIST << ".Artist " 
                << AUDIO_ALBUM << ".Album " 
                << AUDIO_YEAR << ".Year " 
                << AUDIO_TRACK << ".Track " 
                << AUDIO_GENRE << ".Genre " 
                << AUDIO_BACK << ".Go Back\n";
    std::cout << "==========================================================" << std::endl;
}

void MetadataView::menuEditVideo() {
    std::cout << "===========Video Edit ===========" << std::endl;
    std::cout << VIDEO_TITLE << ".Title " 
                << VIDEO_BACK << ".Go Back\n";
    std::cout << "=================================" << std::endl;
}


