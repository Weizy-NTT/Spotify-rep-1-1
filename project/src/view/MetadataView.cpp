#include "MetadataView.hpp"
#include <iostream>

void MetadataView::showMenu() {
    BaseView::showMenu();
    std::cout << "===== Metadata Menu =====" << std::endl;
    std::cout << MetadataMenu::EDIT_METADATA << ". Edit File Metadata\n";
    std::cout << MetadataMenu::BACK_FROM_METADATA << ". Go Back\n";
    std::cout << "=========================" << std::endl;
}

void MetadataView::hideMenu() {
    BaseView::hideMenu();
    std::cout << "Hiding Metadata View...\n";
    std::system("clear");
}

void MetadataView::showFileMetadata(const std::shared_ptr<MediaFile>& file) {
    auto metadata = file->getMetadata();

    std::cout << "File Metadata:\n";
    for (const auto& entry : metadata.getMetadata()) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
}


