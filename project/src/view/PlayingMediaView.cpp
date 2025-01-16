#include "PlayingMediaView.hpp"
#include <iomanip>
#include <mutex>

extern std::mutex mediaMutex;
void PlayingMediaView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Now Playing =====" << std::endl;
    std::cout << PlayingMediaMenu::PLAY << ". Play\n";
    std::cout << PlayingMediaMenu::PAUSE << ". Pause\n";
    std::cout << PlayingMediaMenu::NEXT << ". Next Song\n";
    std::cout << PlayingMediaMenu::PREV << ". Previous Song\n";
    std::cout << PlayingMediaMenu::BACK_FROM_PLAYING << ". Go Back\n";
    std::cout << "======================" << std::endl;
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