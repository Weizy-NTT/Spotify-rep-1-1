#include "MetadataView.hpp"
#include <iostream>
#include <iomanip>

void MetadataView::showMenu() {
    BaseView::showMenu();
    
    constexpr int MENU_WIDTH = 66; // Độ rộng của menu, khớp với các bảng trước đó

    // Hàm vẽ đường viền trên/dưới
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Metadata Menu";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị các tùy chọn menu
    std::cout << "| " << MetadataMenu::EDIT_METADATA << ". Edit File Metadata"
              << std::string(MENU_WIDTH - 22, ' ') << "|\n";
    std::cout << "| " << MetadataMenu::BACK_FROM_METADATA << ". Go Back"
              << std::string(MENU_WIDTH - 11, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}


void MetadataView::hideMenu() {
    BaseView::hideMenu();
    std::system("clear");
}

void MetadataView::showFileMetadata(const std::shared_ptr<MediaFile>& file) {

    constexpr int PROPERTY_WIDTH = 25; // Width for Properties column
    constexpr int VALUE_WIDTH = 36;   // Width for Value column

    auto drawLine = []() {
        std::cout << "+" << std::string(PROPERTY_WIDTH + 2, '-') << "+"
                  << std::string(VALUE_WIDTH + 2, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề metadata, căn giữa
    std::string title = "METADATA OF " + file->getName();
    if (title.size() > PROPERTY_WIDTH + VALUE_WIDTH + 3) {
        title = title.substr(0, PROPERTY_WIDTH + VALUE_WIDTH - 5) + "..."; // Cắt ngắn nếu tiêu đề quá dài
    }
    int padding = ((PROPERTY_WIDTH + VALUE_WIDTH + 5) - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(PROPERTY_WIDTH + VALUE_WIDTH + 5 - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị header cột
    std::cout << "| " << std::left << std::setw(PROPERTY_WIDTH) << "Properties"
              << " | " << std::left << std::setw(VALUE_WIDTH) << "Value" << " |\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị metadata
    auto metadata = file->getMetadata();
    for (const auto& entry : metadata.getMetadata()) {
        std::string key = entry.first;
        std::string value = entry.second;

        if (key.size() > PROPERTY_WIDTH) {
            key = key.substr(0, PROPERTY_WIDTH - 3) + "..."; // Cắt ngắn nếu key quá dài
        }
        if (value.size() > VALUE_WIDTH) {
            value = value.substr(0, VALUE_WIDTH - 3) + "..."; // Cắt ngắn nếu value quá dài
        }

        std::cout << "| " << std::left << std::setw(PROPERTY_WIDTH) << key
                  << " | " << std::left << std::setw(VALUE_WIDTH) << value << " |\n";
    }

    // Vẽ đường viền dưới
    drawLine();
}



void MetadataView::menuEditAudio() {
    BaseView::showMenu();
    constexpr int MENU_WIDTH = 66; // Độ rộng của menu, đồng bộ với các menu trước đó

    // Hàm vẽ đường viền trên/dưới
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Audio Edit Menu";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị các tùy chọn menu
    std::cout << "| " << AUDIO_TITLE << ". Title" << std::string(MENU_WIDTH - 9, ' ') << "|\n";
    std::cout << "| " << AUDIO_ARTIST << ". Artist" << std::string(MENU_WIDTH - 10, ' ') << "|\n";
    std::cout << "| " << AUDIO_ALBUM << ". Album" << std::string(MENU_WIDTH - 9, ' ') << "|\n";
    std::cout << "| " << AUDIO_YEAR << ". Year" << std::string(MENU_WIDTH - 8, ' ') << "|\n";
    std::cout << "| " << AUDIO_TRACK << ". Track" << std::string(MENU_WIDTH - 9, ' ') << "|\n";
    std::cout << "| " << AUDIO_GENRE << ". Genre" << std::string(MENU_WIDTH - 9, ' ') << "|\n";
    std::cout << "| " << AUDIO_BACK << ". Go Back" << std::string(MENU_WIDTH - 11, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}

void MetadataView::menuEditVideo() {
    BaseView::showMenu();
    constexpr int MENU_WIDTH = 66; // Độ rộng của menu, đồng bộ với các menu trước đó

    // Hàm vẽ đường viền trên/dưới
    auto drawLine = []() {
        std::cout << "+" << std::string(MENU_WIDTH, '-') << "+" << "\n";
    };

    // Vẽ đường viền trên
    drawLine();

    // Tiêu đề menu, căn giữa
    std::string title = "Video Edit Menu";
    int padding = (MENU_WIDTH - title.size()) / 2;
    std::cout << "|" << std::string(padding, ' ') << title
              << std::string(MENU_WIDTH - title.size() - padding, ' ') << "|\n";

    // Vẽ đường ngăn cách
    drawLine();

    // Hiển thị các tùy chọn menu
    std::cout << "| " << VIDEO_TITLE << ". Title" << std::string(MENU_WIDTH - 10, ' ') << "|\n";
    std::cout << "| " << VIDEO_BACK << ". Go Back" << std::string(MENU_WIDTH - 12, ' ') << "|\n";

    // Vẽ đường viền dưới
    drawLine();
}


