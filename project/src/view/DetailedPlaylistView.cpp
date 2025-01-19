#include "DetailedPlaylistView.hpp"
#include <iomanip>

void DetailedPlaylistView::showMenu() {
    BaseView::showMenu();

    constexpr int MENU_WIDTH = 66; // Chiều rộng của menu, khớp với bảng

    // Hàm vẽ đường viền trên/dưới
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Detailed Playlist Menu";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị các tùy chọn menu, sử dụng enum
    std::cout << "| " << DetailedPlaylistMenu::PLAY_SONG_FROM_PLAYLIST
              << ". Play a song" << std::string(MENU_WIDTH - 15, ' ') << "|\n";
    std::cout << "| " << DetailedPlaylistMenu::ADD_SONG
              << ". Add a song to playlist" << std::string(MENU_WIDTH - 26, ' ') << "|\n";
    std::cout << "| " << DetailedPlaylistMenu::DELETE_SONG
              << ". Delete a song from playlist" << std::string(MENU_WIDTH - 31, ' ') << "|\n";
    std::cout << "| " << DetailedPlaylistMenu::SHOW_DETAIL_SONG
              << ". Show details of a song" << std::string(MENU_WIDTH - 26, ' ') << "|\n";
    std::cout << "| " << DetailedPlaylistMenu::BACK_FROM_DETAIL
              << ". Go Back" << std::string(MENU_WIDTH - 11, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}

void DetailedPlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::system("clear");
}

void DetailedPlaylistView::showListOfSongs(const std::shared_ptr<Playlist>& playlist) {
    constexpr int ID_WIDTH = 5;         // Width for ID column
    constexpr int NAME_WIDTH = 30;     // Width for Name column
    constexpr int DURATION_WIDTH = 10; // Width for Duration column
    constexpr int TYPE_WIDTH = 10;     // Width for Type column

    auto drawLine = []() {
        std::cout << "+" << std::string(ID_WIDTH + 2, '-') << "+"
                  << std::string(NAME_WIDTH + 2, '-') << "+"
                  << std::string(DURATION_WIDTH + 2, '-') << "+"
                  << std::string(TYPE_WIDTH + 2, '-') << "+" << "\n";
    };

    // Draw top border
    drawLine();

    // Display centered header with playlist name
    std::string title = "Songs in Playlist: " + playlist->getName();
    int totalWidth = ID_WIDTH + NAME_WIDTH + DURATION_WIDTH + TYPE_WIDTH + 9; // +9 for separators and spaces
    int padding = (totalWidth - title.size()) / 2;                           // Calculate padding
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(totalWidth - title.size() - padding + 2, ' ') << "|\n";

    // Draw separator line
    drawLine();

    // Display table header
    std::cout << "| " << std::left << std::setw(ID_WIDTH) << "ID" << " | "
              << std::left << std::setw(NAME_WIDTH) << "Name" << " | "
              << std::left << std::setw(DURATION_WIDTH) << "Duration" << " | "
              << std::left << std::setw(TYPE_WIDTH) << "Type" << " |\n";

    // Draw separator line
    drawLine();

    // Fetch and display songs in the playlist
    std::vector<std::shared_ptr<MediaFile>> songs = playlist->getSongs();
    for (size_t i = 0; i < songs.size(); ++i) {
        // Truncate Name column if it exceeds NAME_WIDTH
        std::string truncatedName = songs[i]->getName();
        if (truncatedName.size() > NAME_WIDTH - 3) {
            truncatedName = truncatedName.substr(0, NAME_WIDTH - 3) + "...";
        }

        // Map type to string
        std::string typeStr = (songs[i]->getType() == 1) ? "VIDEO" : "AUDIO";

        std::cout << "| " << std::left << std::setw(ID_WIDTH) << songs[i]->getID() << " | "
                  << std::left << std::setw(NAME_WIDTH) << truncatedName << " | "
                  << std::left << std::setw(DURATION_WIDTH) << songs[i]->getMetadata().getValue("Duration") << " | "
                  << std::left << std::setw(TYPE_WIDTH) << typeStr << " |\n";
    }

    // Draw bottom border
    drawLine();
}

void DetailedPlaylistView::displayStatusMessage(DetailedPlaylistStatus& status) {
    switch (status) {
        case DetailedPlaylistStatus::DETAILED_ADD_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in media library or Song ID exists in playlist. Cannot add.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_PLAY_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot play.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_DELETE_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot delete.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_SHOW_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot show.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_NORMAL:
        default:
            break;
    }
}
