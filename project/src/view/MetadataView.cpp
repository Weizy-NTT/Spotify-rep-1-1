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

    std::cout << "Metadata of " << file->getName() << std::endl;
    for (const auto& entry : metadata.getMetadata()) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
}

void MetadataView::menuEditAudio() {
    std::cout << "======================= Audio Edit =======================" << std::endl;
    std::cout << AUDIO_TITLE << ".Title " 
                << AUDIO_ARTIST << ".Artist " 
                << AUDIO_ALBUM << ".Album " 
                << AUDIO_YEAR << ".Year " 
                << AUDIO_TRACK << ".Track " 
                << AUDIO_GENRE << ".Genre " 
                << AUDIO_BACK << ".Go Back\n";
    std::cout << "==========================================================" << std::endl;
}

void MetadataView::menuEditVideo() {
    std::cout << "===========Video Edit ===========" << std::endl;
    std::cout << VIDEO_TITLE << ".Title " 
                << VIDEO_BACK << ".Go Back\n";
    std::cout << "=================================" << std::endl;
}


