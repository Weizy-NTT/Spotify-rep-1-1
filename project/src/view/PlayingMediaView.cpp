
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

void PlayingMediaView::showPlayingMedia(const std::shared_ptr<MediaFile>& file, size_t& currentTime, size_t totalTime, int& volume) {
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

        // Tạo thanh tiến trình bài hát
        std::vector<Element> progress_bar_elements(barWidth, text("="));
        std::fill(progress_bar_elements.begin(), progress_bar_elements.begin() + pos, text("#"));
        auto progress_bar = hbox({
            text("["), 
            hbox(progress_bar_elements), 
            text("]")
        });

        // Tạo thanh âm lượng
        int volumeBarWidth = 30;
        int volumePos = static_cast<int>(volumeBarWidth * (volume / 128.0));
        std::vector<Element> volume_bar_elements(volumeBarWidth, text("="));
        std::fill(volume_bar_elements.begin(), volume_bar_elements.begin() + volumePos, text("#"));
        auto volume_bar = hbox({
            text("["), 
            hbox(volume_bar_elements), 
            text("]")
        });

        // Hiển thị % volume
        std::string volumePercent = std::to_string(static_cast<int>((volume / 128.0) * 100)) + "%";

        // Kết hợp thông tin bài hát, thanh tiến trình, và âm lượng
        return vbox({
                text("===== Now Playing ====="),
                text("Song: " + file->getName() + " - " + file->getMetadata().getMetadata()["Artist"]) | bold | color(Color::Green),
                progress_bar | color(Color::Yellow),
                text(current + " / " + total) | color(Color::Red),
                separator(),
                hbox({
                    text("Volume: "),
                    volume_bar,
                    text(" " + volumePercent) | color(Color::White)
                }) | color(Color::Cyan),
                menu->Render(),
                text("======================="),
                text("Use arrow keys to navigate, press Enter to select.") | color(Color::Red),
            }) |
            border;
    });

    // Luồng cập nhật giao diện
    std::thread refresh_thread([&] {
        size_t lastTime = currentTime;
        int lastVolume = volume;
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (lastTime != currentTime || lastVolume != volume) {
                lastTime = currentTime;
                lastVolume = volume;
                screen.PostEvent(Event::Custom); // Làm mới giao diện khi thời gian hoặc âm lượng thay đổi
            }
        }
    });

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

    // Dừng luồng cập nhật
    running = false;
    if (refresh_thread.joinable()) {
        refresh_thread.join();
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

void PlayingMediaView::showMenu() {
    BaseView::showMenu();
    std::cout << "Hiding Playing Media View...\n";
    std::system("clear");
}
