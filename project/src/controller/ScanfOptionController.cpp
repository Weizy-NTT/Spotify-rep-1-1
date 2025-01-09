#include "ScanfOptionController.hpp"
#include <iostream>
#include "ScanfOptionView.hpp"
#include "ControllerManager.hpp"

std::vector<MediaFile> ScanfOptionController::scanDirectory(const std::string& path) {
    std::vector<MediaFile> files;
    // TODO: Thêm logic quét directory
    MediaFile media1;
    media1.setName("Song 1");
    media1.setPath("/path/to/song");

    // Đảm bảo gọi setType và setMetadata trước khi truy xuất
    media1.setType(AUDIO);
    Metadata metadata1;
    metadata1.setValue("artist", "Artist Name");
    media1.setMetadata(metadata1);
    files.push_back(media1);

    MediaFile media;
    media.setName("Song 12");
    media.setPath("/path/to/song");

    // Đảm bảo gọi setType và setMetadata trước khi truy xuất
    media.setType(AUDIO);
    Metadata metadata;
    metadata.setValue("artist", "Artist Name");
    media.setMetadata(metadata);
    files.push_back(media);

    std::cout << "Đang quét thư mục: " << path << "\n";
    return files;
}

std::vector<MediaFile> ScanfOptionController::scanUSBDevice() {
    std::vector<MediaFile> files;
    // TODO: Thêm logic quét USB
    std::cout << "Đang quét USB...\n";
    return files;
}

