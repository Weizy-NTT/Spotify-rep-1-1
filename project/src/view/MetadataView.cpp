#include "MetadataView.hpp"
#include <iostream>
#include <iomanip>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // Để dùng text, vbox, border

using namespace ftxui;
void MetadataView::showMenu() {
    BaseView::showMenu();
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

        // Sự kiện nhấn Enter (tương tự chuột trái)
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
        text("Metadata Editing") | dim | hcenter
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
    BaseView::showMenu();
    
    std::vector<std::string> audio_edit_entries = {
        "Edit Title",
        "Edit Artist",
        "Edit Album",
        "Edit Year",
        "Edit Track",
        "Edit Genre",
        "Back"
    };
    
    // Tạo menu cho Audio Edit
    auto menu_audio = Menu(&audio_edit_entries, &selected_option_audio);

    // Tạo renderer để hiển thị menu Audio Edit
    auto renderer_audio = Renderer(menu_audio, [&] {
        return vbox({
            text("===== Audio Edit Menu =====") | bold | center,
            menu_audio->Render(),
            text("==========================="),
            text("Use arrow keys or mouse to navigate, press Enter or click to select."),
        }) |
        border;
    });

    // Tạo đối tượng ScreenInteractive để xử lý sự kiện
    auto screen = ScreenInteractive::TerminalOutput();

    auto event_handler = CatchEvent(renderer_audio, [&](Event event) {
    // Xử lý sự kiện chuột cho Audio Edit
    if (event.is_mouse()) {
        if (event.mouse().button == Mouse::Left && menu_audio->OnEvent(event)) {
            std::cout << "Audio Option " << selected_option_audio << " selected via mouse!" << std::endl;
            screen.ExitLoopClosure()();  // Thoát vòng lặp khi click vào menu
            return true;
        }
    }

    // Sự kiện nhấn Enter (tương tự chuột trái)
    if (event == Event::Return) {
        if (menu_audio->OnEvent(event)) {
            screen.ExitLoopClosure()();
            return true;
        }
    }

    // Xử lý sự kiện bàn phím (ESC hoặc q để thoát)
    if (event == Event::Escape || event == Event::Character('q')) {
        std::cout << "Exiting Audio Edit menu..." << std::endl;
        screen.ExitLoopClosure()(); // Thoát vòng lặp khi nhấn ESC hoặc 'q'
        return true;
    }

    // Tiếp tục xử lý sự kiện khác, nếu không phải chuột hoặc phím ESC/q
    return menu_audio->OnEvent(event);  // Tiếp tục xử lý sự kiện của menu
});

    // Chạy vòng lặp giao diện
    screen.Loop(event_handler);
    // std::system("clear");  // Làm sạch màn hình sau khi thoát vòng lặp
}


void MetadataView::menuEditVideo() {
    BaseView::showMenu();
    
    // Menu cho Video Edit
    std::vector<std::string> video_edit_entries = {
        "Edit Title",
        "Back"
    };

    // Tạo menu cho Video Edit
    auto menu_video = Menu(&video_edit_entries, &selected_option_video);

    // Tạo renderer để hiển thị menu Video Edit
    auto renderer_video = Renderer(menu_video, [&] {
        return vbox({
            text("===== Video Edit Menu =====") | bold | hcenter,
            menu_video->Render(),
            text("==========================="),
            text("Use arrow keys or mouse to navigate, press Enter or click to select."),
        }) |
        border;
    });

    // Tạo đối tượng ScreenInteractive để xử lý sự kiện
    auto screen = ScreenInteractive::TerminalOutput();

    // Xử lý sự kiện chuột và bàn phím
    auto event_handler = CatchEvent(renderer_video,[&](Event event) {
        // Xử lý sự kiện chuột cho Video Edit
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left&& menu_video->OnEvent(event)) {
                std::cout << "Video Option " << selected_option_video << " selected via mouse!" << std::endl;
                screen.ExitLoopClosure()();  // Thoát vòng lặp khi click vào menu
                return true;
            }
        }

        // Sự kiện nhấn Enter (tương tự chuột trái)
        if (event == Event::Return) {
            if (menu_video->OnEvent(event)) {
                screen.ExitLoopClosure()();
                return true;
            }
        }

        // Xử lý sự kiện bàn phím (ESC hoặc q để thoát)
        if (event == Event::Escape || event == Event::Character('q')) {
            std::cout << "Exiting Video Edit menu..." << std::endl;
            screen.ExitLoopClosure()(); // Thoát vòng lặp khi nhấn ESC hoặc 'q'
            return true;
        }

        return menu_video->OnEvent(event);  // Tiếp tục xử lý sự kiện khác
    });

    // Chạy vòng lặp giao diện
    screen.Loop(event_handler);
    // std::system("clear");  // Làm sạch màn hình sau khi thoát vòng lặp
}

int MetadataView::getAuditoOption() const{
    return selected_option_audio;
}

int MetadataView::getVideoOption() const{
    return selected_option_video;
}


