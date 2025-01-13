#include "PlayingMediaView.hpp"

void PlayingMediaView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Now Playing =====" << std::endl;
    std::cout << PlayingMediaMenu::PLAY_PAUSE << ". Play/Pause\n";
    std::cout << PlayingMediaMenu::NEXT << ". Next Song\n";
    std::cout << PlayingMediaMenu::PREV << ". Previous Song\n";
    std::cout << PlayingMediaMenu::VOLUME << ". Adjust Volume\n";
    std::cout << PlayingMediaMenu::BACK_FROM_PLAYING << ". Go Back\n";
    std::cout << "======================" << std::endl;
}

void PlayingMediaView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Playing Media View...\n";
    std::system("clear");
}

void PlayingMediaView::showSongInfo(const std::shared_ptr<MediaFile>& file) {
    auto metadata = file->getMetadata();
    std::cout << "Now Playing: " << file->getName() << " - " << metadata.getMetadata()["Artist"] << std::endl;
}
