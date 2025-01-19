#include "PlayingMediaView.hpp"
#include <iomanip>
#include <mutex>

extern std::mutex mediaMutex;
void PlayingMediaView::showMenu() {
    BaseView::showMenu();
    
    constexpr int MENU_WIDTH = 66; // Độ rộng của menu, đồng bộ với các menu trước đó

    // Hàm vẽ đường viền trên/dưới
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Media Player Menu";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị các tùy chọn menu
    std::cout << "| " << PlayingMediaMenu::PLAY << ". Play" << std::string(MENU_WIDTH - 8, ' ') << "|\n";
    std::cout << "| " << PlayingMediaMenu::PAUSE << ". Pause" << std::string(MENU_WIDTH - 9, ' ') << "|\n";
    std::cout << "| " << PlayingMediaMenu::NEXT << ". Next Song" << std::string(MENU_WIDTH - 13, ' ') << "|\n";
    std::cout << "| " << PlayingMediaMenu::PREV << ". Previous Song" << std::string(MENU_WIDTH - 17, ' ') << "|\n";
    std::cout << "| " << PlayingMediaMenu::BACK_FROM_PLAYING << ". Go Back" << std::string(MENU_WIDTH - 11, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}

void PlayingMediaView::hideMenu() {
    BaseView::hideMenu();
    std::system("clear");
}

void PlayingMediaView::showSongInfo(const std::shared_ptr<MediaFile>& file, size_t currentTime, size_t totalTime, int volumeLevel) {
    constexpr int MENU_WIDTH = 66; // Độ rộng của menu
    constexpr int BAR_WIDTH = 40; // Độ rộng thanh tiến trình
    constexpr int VOLUME_BAR_WIDTH = 40; // Độ rộng thanh âm lượng

    // Hàm vẽ đường viền
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Tính toán thời gian
    std::string current = (currentTime / 60 < 10 ? "0" : "") + std::to_string(currentTime / 60) + ":" +
                          (currentTime % 60 < 10 ? "0" : "") + std::to_string(currentTime % 60);

    std::string total = (totalTime / 60 < 10 ? "0" : "") + std::to_string(totalTime / 60) + ":" +
                        (totalTime % 60 < 10 ? "0" : "") + std::to_string(totalTime % 60);

    float progress = static_cast<float>(currentTime) / totalTime;
    int pos = static_cast<int>(BAR_WIDTH * progress);

    // Vẽ thông tin Now Playing
    drawLine();
    std::string title = "Now Playing";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";
    drawLine();

    // Hiển thị Title
    std::string songTitle = file->getMetadata().getValue("Title");
    std::cout << "| Title: " << std::left << std::setw(58) << songTitle << "|\n";

    // Hiển thị Artist
    std::string artist = file->getMetadata().getValue("Artist");
    std::cout << "| Artist: " << std::left << std::setw(57) << artist << "|\n";
    drawLine();

    // Hiển thị thanh tiến trình
    std::cout << "| Process:[";
    for (int i = 0; i < BAR_WIDTH; ++i) {
        if (i < pos) {
            std::cout << "#";
        } else {
            std::cout << "=";
        }
    }
    std::cout << "] " << current << "/" << total << " " << std::string(2, ' ') << "|\n";
    drawLine();

    // Hiển thị thanh âm lượng
    std::cout << "| Volume: [";
    int volumePos = static_cast<int>((VOLUME_BAR_WIDTH * volumeLevel) / 127);
    for (int i = 0; i < VOLUME_BAR_WIDTH; ++i) {
        if (i < volumePos) {
            std::cout << "#";
        } else {
            std::cout << "=";
        }
    }
    std::cout << "] " << volumeLevel*100/127 << "%" << std::string(10, ' ') << "|\n";
    drawLine();
}
