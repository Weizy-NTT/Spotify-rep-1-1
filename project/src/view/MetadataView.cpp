#include "MetadataView.hpp"
#include <iostream>

// Hiển thị menu với các lựa chọn: xem metadata, chỉnh sửa metadata
void MetadataView::showMenu() {
    BaseView::showMenu();  // Hiển thị menu của lớp cơ sở
    std::cout << "===== Metadata Menu =====\n";
    std::cout << "1. Show File Metadata\n";
    std::cout << "2. Edit File Metadata\n";
    std::cout << "0. Go Back\n";
    std::cout << "=========================\n";
}

// Ẩn menu (nếu cần)
void MetadataView::hideMenu() {
    // Có thể thực hiện việc ẩn menu nếu cần
}

// Hiển thị thông tin metadata của file media
void MetadataView::showFileMetadata(const MediaFile& file) {
    std::cout << "===== File Metadata =====\n";
    std::cout << "File Name: " << file.getName() << std::endl;  // Giả sử MediaFile có phương thức getName()
    std::cout << "Duration: " << file.getDuration() << " seconds" << std::endl;  // Giả sử MediaFile có phương thức getDuration()
    std::cout << "Artist: " << file.getArtist() << std::endl;  // Giả sử MediaFile có phương thức getArtist()
    std::cout << "Album: " << file.getAlbum() << std::endl;  // Giả sử MediaFile có phương thức getAlbum()
    std::cout << "=========================\n";
}

// Chỉnh sửa thông tin metadata của file media
void MetadataView::editFileMetadata(MediaFile& file) {
    std::string newArtist, newAlbum;
    std::cout << "Enter new artist name: ";
    std::getline(std::cin, newArtist);
    file.setArtist(newArtist);  // Giả sử MediaFile có phương thức setArtist()

    std::cout << "Enter new album name: ";
    std::getline(std::cin, newAlbum);
    file.setAlbum(newAlbum);  // Giả sử MediaFile có phương thức setAlbum()

    std::cout << "Metadata updated successfully!\n";
}

// Xử lý đầu vào (Override từ BaseView)
void MetadataView::handleInput(const std::string& input) {
    if (input == "1") {
        std::cout << "Displaying file metadata...\n";
        // Giả sử bạn đã có đối tượng `file` để hiển thị metadata
        // showFileMetadata(file);
    } else if (input == "2") {
        std::cout << "Editing file metadata...\n";
        // Giả sử bạn đã có đối tượng `file` để chỉnh sửa metadata
        // editFileMetadata(file);
    } else if (input == "0") {
        std::cout << "Going back to the previous menu...\n";
        // Quay lại menu trước
    } else {
        std::cout << "Invalid option. Please try again.\n";
    }
}
