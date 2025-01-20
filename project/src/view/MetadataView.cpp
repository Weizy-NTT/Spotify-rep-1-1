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
void MetadataView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Metadata View...\n";
    std::system("clear");
}

int MetadataView::getSelectedOption() const {
    return selected_option;
}

void MetadataView::showFileMetadata(const std::shared_ptr<MediaFile>& file) {
    using namespace ftxui;

    auto metadata = file->getMetadata();

    // 1. Tạo tiêu đề
    auto header = hbox({
        text("METADATA OF: ") | bold,
        text(file->getName()) | color(Color::Yellow)
    }) | hcenter;

    // 2. Tạo nội dung metadata
    Elements rows;
    for (const auto& entry : metadata.getMetadata()) {
        rows.push_back(hbox({
            text(entry.first + ":") | size(WIDTH, EQUAL, 15),   // Tên thuộc tính
            text(entry.second) | size(WIDTH, GREATER_THAN, 25) // Giá trị
        }));
    }

    auto content = vbox(std::move(rows)) | border;

    // 3. Tạo giao diện tổng thể
    auto document = vbox({
        header,
        separator(),
        content,
        separator(),
        text("Press any key to continue...") | dim | hcenter
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

void MetadataView::menuEditAudio() {
    using namespace ftxui;

    // 1. Tạo danh sách menu
    auto menu_items = vbox({
        hbox({text(std::to_string(AUDIO_TITLE) + ". Title") | size(WIDTH, EQUAL, 20)}),
        hbox({text(std::to_string(AUDIO_ARTIST) + ". Artist") | size(WIDTH, EQUAL, 20)}),
        hbox({text(std::to_string(AUDIO_ALBUM) + ". Album") | size(WIDTH, EQUAL, 20)}),
        hbox({text(std::to_string(AUDIO_YEAR) + ". Year") | size(WIDTH, EQUAL, 20)}),
        hbox({text(std::to_string(AUDIO_TRACK) + ". Track") | size(WIDTH, EQUAL, 20)}),
        hbox({text(std::to_string(AUDIO_GENRE) + ". Genre") | size(WIDTH, EQUAL, 20)}),
        hbox({text(std::to_string(AUDIO_BACK) + ". Go Back") | size(WIDTH, EQUAL, 20)})
    }) | border;

    // 2. Tạo tiêu đề
    auto header = text("================ Audio Edit ================") | bold | hcenter;

    // 3. Kết hợp giao diện
    auto document = vbox({
        header,
        separator(),
        menu_items,
        separator(),
        text("Use arrow keys or enter a number to select.") | dim | hcenter
    });

    // 4. Điều chỉnh màn hình
    auto screen = Screen::Create(
        Dimension::Full(),        // Chiều rộng tự động chiếm hết
        Dimension::Fit(document)  // Chiều cao tự động vừa nội dung
    );
    Render(screen, document);

    // 5. Hiển thị giao diện
    std::cout << screen.ToString() << std::endl;
}

void MetadataView::menuEditVideo() {
    using namespace ftxui;

    // 1. Tạo danh sách menu
    auto menu_items = vbox({
        hbox({text(std::to_string(VIDEO_TITLE) + ". Title") | size(WIDTH, EQUAL, 20)}),
        hbox({text(std::to_string(VIDEO_BACK) + ". Go Back") | size(WIDTH, EQUAL, 20)})
    }) | border;

    // 2. Tạo tiêu đề
    auto header = text("=========== Video Edit ===========") | bold | hcenter;

    // 3. Kết hợp giao diện
    auto document = vbox({
        header,
        separator(),
        menu_items,
        separator(),
        text("Use arrow keys or enter a number to select.") | dim | hcenter
    });

    // 4. Điều chỉnh màn hình
    auto screen = Screen::Create(
        Dimension::Full(),        // Chiều rộng tự động chiếm hết
        Dimension::Fit(document)  // Chiều cao tự động vừa nội dung
    );
    Render(screen, document);

    // 5. Hiển thị giao diện
    std::cout << screen.ToString() << std::endl;
}

