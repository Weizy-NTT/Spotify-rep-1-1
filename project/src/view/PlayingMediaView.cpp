#include "PlayingMediaView.hpp"
#include <iomanip>
#include <mutex>

extern std::mutex mediaMutex;
#include "PlayingMediaView.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // Để dùng text, vbox, border

using namespace ftxui;

void PlayingMediaView::showMenu() {
    // Tạo menu với các mục
    auto menu = Menu(&menu_entries, &selected_option);

    // Tạo renderer để hiển thị menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Now Playing ====="),
                   menu->Render(),
                   text("======================="),
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

int PlayingMediaView::getSelectedOption() const {
    return selected_option;
}

void PlayingMediaView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Playing Media View...\n";
    std::system("clear");
}

void PlayingMediaView::showSongInfo(const std::shared_ptr<MediaFile>& file, size_t currentTime, size_t totalTime) {
    auto metadata = file->getMetadata();
    std::string current = (currentTime / 60 < 10 ? "0" : "") + std::to_string(currentTime / 60) + ":" +
                        (currentTime % 60 < 10 ? "0" : "") + std::to_string(currentTime % 60);

    std::string total = (totalTime / 60 < 10 ? "0" : "") + std::to_string(totalTime / 60) + ":" +
                        (totalTime % 60 < 10 ? "0" : "") + std::to_string(totalTime % 60);

    float progress = static_cast<float>(currentTime) / totalTime;

    // Số lượng ký tự sẽ hiển thị trong thanh tiến trình
    int barWidth = 50;

    // Tính toán số lượng ký tự cần hiển thị
    int pos = static_cast<int>(barWidth * progress);

    std::cout   << " Now Playing: " << file->getName() << " - " 
                << metadata.getMetadata()["Artist"] << std::endl;
    // Hiển thị thanh tiến trình
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) {
            std::cout << "#";  // Phần đã trôi qua
        } else {
            std::cout << "=";  // Phần chưa trôi qua
        }
    }
    std::cout << "] " << current << "/" << total << std::endl;  // Hiển thị phần trăm
    std::cout.flush();

}