#include "PlaylistView.hpp"
#include <iostream>
#include <iomanip>

void PlaylistView::showMenu() {
    BaseView::showMenu();

    constexpr int MENU_WIDTH = 66; // Độ rộng của menu, đồng bộ với các menu khác

    // Hàm vẽ đường viền trên/dưới
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Playlist Menu";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị các tùy chọn menu
    std::cout << "| " << PlaylistMenu::SELECT_PLAYLIST << ". Select a Playlist" << std::string(MENU_WIDTH - 21, ' ') << "|\n";
    std::cout << "| " << PlaylistMenu::ADD_PLAYLIST << ". Add a Playlist" << std::string(MENU_WIDTH - 18, ' ') << "|\n";
    std::cout << "| " << PlaylistMenu::REMOVE_PLAYLIST << ". Remove a Playlist" << std::string(MENU_WIDTH - 21, ' ') << "|\n";
    std::cout << "| " << PlaylistMenu::BACK_FROM_PLAYLIST << ". Go Back" << std::string(MENU_WIDTH - 11, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}

void PlaylistView::hideMenu() {
    BaseView::hideMenu();
    std::system("clear");
}

void PlaylistView::showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists) {
    constexpr int ID_WIDTH = 10;         // Width for ID column
    constexpr int NAME_WIDTH = 30;      // Width for Name column
    constexpr int SONGS_WIDTH = 18;     // Width for Songs column

    auto drawLine = []() {
        std::cout << "+" << std::string(ID_WIDTH + 2, '-') << "+"
                  << std::string(NAME_WIDTH + 2, '-') << "+"
                  << std::string(SONGS_WIDTH + 2, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Playlist List";
    int totalWidth = ID_WIDTH + NAME_WIDTH + SONGS_WIDTH + 9; // +9 for separators and spaces
    int padding = (totalWidth - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(totalWidth - title.size() - padding - 1, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị header cột
    std::cout << "| " << std::left << std::setw(ID_WIDTH) << "ID" << " | "
              << std::left << std::setw(NAME_WIDTH) << "Name" << " | "
              << std::left << std::setw(SONGS_WIDTH) << "Songs" << " |\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị danh sách playlist
    for (size_t i = 0; i < playlists.size(); ++i) {
        std::cout << "| " << std::left << std::setw(ID_WIDTH) << playlists[i]->getID() << " | "
                  << std::left << std::setw(NAME_WIDTH) << playlists[i]->getName() << " | "
                  << std::left << std::setw(SONGS_WIDTH) << playlists[i]->getSongs().size() << " |\n";
    }

    // Vẽ đường viền dưới
    drawLine();
}

void PlaylistView::displayStatusMessage(PlaylistStatus& status) {
    switch (status) {
        case PlaylistStatus::PLAYLIST_SELECT_STATUS:
            std::cout << "Error: The playlist ID was not found in the library.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_ADD_STATUS:
            std::cout << "Error: Could not add playlist. Please try again.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_REMOVE_STATUS:
            std::cout << "Error: The playlist ID was not found in the library. Could not remove.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset trạng thái sau khi thông báo lỗi
            break;
        case PlaylistStatus::PLAYLIST_NORMAL:
        default:
            // Không cần thông báo khi ở trạng thái bình thường
            break;
    }
}



