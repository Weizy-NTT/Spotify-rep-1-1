
#include "PlayingMediaView.hpp"
#include <iomanip>
#include <mutex>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <thread>
#include <atomic>
#include <chrono>

using namespace ftxui;
void PlayingMediaView::showMenu() {
    std::cout << "aaaa\n";
}
void PlayingMediaView::showPlayingMedia(const std::shared_ptr<MediaFile>& file, size_t initialTime, size_t totalTime, bool paused) {
    // Thời gian hiện tại (cập nhật liên tục)
    std::atomic<size_t> currentTime = initialTime;
    bool running = true;

    // Tạo menu với các mục
    auto menu = Menu(&menu_entries, &selected_option);

    // Tạo màn hình tương tác
    auto screen = ScreenInteractive::TerminalOutput();

    // Giao diện hiển thị
    auto renderer = Renderer(menu, [&] {
        // Hiển thị thông tin bài hát
        std::string current = (currentTime / 60 < 10 ? "0" : "") + std::to_string(currentTime / 60) + ":" +
                              (currentTime % 60 < 10 ? "0" : "") + std::to_string(currentTime % 60);
        std::string total = (totalTime / 60 < 10 ? "0" : "") + std::to_string(totalTime / 60) + ":" +
                            (totalTime % 60 < 10 ? "0" : "") + std::to_string(totalTime % 60);

        float progress = static_cast<float>(currentTime) / totalTime;
        int barWidth = 50;
        int pos = static_cast<int>(barWidth * progress);

        // Tạo thanh tiến trình
        std::vector<Element> progress_bar_elements(barWidth, text("=")); // Ban đầu tất cả là "="
        std::fill(progress_bar_elements.begin(), progress_bar_elements.begin() + pos, text("#")); // Thay thế "#" dựa trên tiến trình
        auto progress_bar = hbox({
            text("["),
            hbox(progress_bar_elements),
            text("]"),
        });
        // Kết hợp thông tin bài hát và menu
        return vbox({
                   text("===== Now Playing ====="),
                   text("Song: " + file->getName() + " - " + file->getMetadata().getMetadata()["Artist"]) | bold | color(Color::Green),
                   progress_bar | color(Color::Yellow),
                   text(current + " / " + total) | color(Color::Blue),
                   separator(),
                   menu->Render(), // Hiển thị menu
                   text("======================="),
                   text("Use arrow keys or mouse to navigate, press Enter or click to select.") | color(Color::Red),
               }) |
               border;
    });

    // Luồng cập nhật thời gian hiện tại
    std::thread update_thread([&] {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Cập nhật mỗi giây
            if (!paused && (currentTime < totalTime)) {
                currentTime++;
                screen.PostEvent(Event::Custom); // Kích hoạt làm mới giao diện
            } else {
                running = false; // Tự động dừng khi kết thúc bài hát
                screen.Exit();
            }
        }
    });

    // Xử lý sự kiện
    auto event_handler = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left && menu->OnEvent(event)) {
                screen.Exit(); // Thoát vòng lặp khi click vào menu
                return true;
            }
        }
        if (event == Event::Escape || event == Event::Character('q')) {
            running = false;
            screen.Exit(); // Thoát vòng lặp khi nhấn ESC hoặc 'q'
            return true;
        }
        return menu->OnEvent(event);
    });

    // Chạy vòng lặp giao diện
    screen.Loop(event_handler);

    // Dừng luồng cập nhật
    running = false;
    if (update_thread.joinable()) {
        update_thread.join();
    }

    std::system("clear");
}

int PlayingMediaView::getSelectedOption() const {
    return selected_option;
}

void PlayingMediaView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Playing Media View...\n";
    std::system("clear");
}
