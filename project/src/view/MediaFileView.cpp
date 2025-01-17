#include "MediaFileView.hpp"
#include <iostream>
#include <iomanip>

void MediaFileView::showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, size_t currentPage, size_t firstSong, size_t lastSong) {
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

    // Display centered page header
    std::string title = "Page " + std::to_string(currentPage);
    int totalWidth = ID_WIDTH + NAME_WIDTH + DURATION_WIDTH + TYPE_WIDTH + 9; // +9 for separators and spaces
    int padding = (totalWidth - title.size()) / 2;
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

    // Display media file rows
    for (size_t i = firstSong; i <= lastSong; ++i) {
        if (i < files.size()) {
            // Truncate Name column if it exceeds NAME_WIDTH
            std::string truncatedName = files[i]->getName();
            if (truncatedName.size() > NAME_WIDTH - 3) {
                truncatedName = truncatedName.substr(0, NAME_WIDTH - 3) + "...";
            }

            // Map type to string
            std::string typeStr = (files[i]->getType() == 1) ? "VIDEO" : "AUDIO";

            std::cout << "| " << std::left << std::setw(ID_WIDTH) << files[i]->getID() << " | "
                      << std::left << std::setw(NAME_WIDTH) << truncatedName << " | "
                      << std::left << std::setw(DURATION_WIDTH) << files[i]->getMetadata().getValue("Duration") << " | "
                      << std::left << std::setw(TYPE_WIDTH) << typeStr << " |\n";
        }
    }

    // Draw bottom border
    drawLine();
}

void MediaFileView::showMenu() {
    BaseView::showMenu();

    constexpr int MENU_WIDTH = 66; // Chiều rộng của menu, đồng bộ với các menu khác

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
    std::cout << "| " << MediaFileMenu::PLAY_SONG_FROM_FILES 
              << ". Play" << std::string(MENU_WIDTH - 8, ' ') << "|\n";
    std::cout << "| " << MediaFileMenu::SHOW_DETAIL 
              << ". Show Media File Details" << std::string(MENU_WIDTH - 27, ' ') << "|\n";
    std::cout << "| " << MediaFileMenu::NEXT_PAGE 
              << ". Show Next Page" << std::string(MENU_WIDTH - 18, ' ') << "|\n";
    std::cout << "| " << MediaFileMenu::PREV_PAGE 
              << ". Show Previous Page" << std::string(MENU_WIDTH - 22, ' ') << "|\n";
    std::cout << "| " << MediaFileMenu::BACK_FROM_MEDIA 
              << ". Go Back" << std::string(MENU_WIDTH - 11, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}


void MediaFileView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Media File View...\n";
    std::system("clear");
}

void MediaFileView::displayStatusMessage(MediaFileStatus& status) {
    switch (status) {
        case MediaFileStatus::MEDIAFILE_PLAY_STATUS:
            std::cout << "Song ID not found in media library. Cannot play.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset lại trạng thái
            break;
        case MediaFileStatus::MEDIAFILE_DETAIL_STATUS:
            std::cout << "Song ID not found in media library. Cannot show details.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset lại trạng thái
            break;
        case MediaFileStatus::MEDIAFILE_NEXT_PAGE_STATUS:
            std::cout << "This is the last page. Cannot go next.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset lại trạng thái
            break;
        case MediaFileStatus::MEDIAFILE_PREV_PAGE_STATUS:
            std::cout << "This is the first page. Cannot go back.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset lại trạng thái
            break;
        case MediaFileStatus::MEDIAFILE_NORMAL:
        default:
            // Không cần thông báo khi ở trạng thái bình thường
            break;
    }
}


