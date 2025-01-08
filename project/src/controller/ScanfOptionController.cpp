#include "ScanfOptionController.hpp"
#include <iostream>
#include "ScanfOptionView.hpp"
#include "ControllerManager.hpp"

std::vector<MediaFile> ScanfOptionController::scanDirectory(const std::string& path) {
    std::vector<MediaFile> files;
    // TODO: Thêm logic quét directory
    MediaFile newMedia1;
    newMedia1.setName("Exist Sign");
    newMedia1.setPath(path);
    files.push_back(newMedia1);

    MediaFile newMedia2;
    newMedia2.setName("Ly Cay Bong");
    newMedia2.setPath(path);
    files.push_back(newMedia2);

    std::cout << "Đang quét thư mục: " << path << "\n";
    return files;
}

std::vector<MediaFile> ScanfOptionController::scanUSBDevice() {
    std::vector<MediaFile> files;
    // TODO: Thêm logic quét USB
    std::cout << "Đang quét USB...\n";
    return files;
}

