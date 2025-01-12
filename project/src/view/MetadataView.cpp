#include "MetadataView.hpp"
#include <iostream>
#include <iomanip>

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

    // Header
    std::cout << "\n+-------------------------------------------------+\n";
    std::cout << "   METADATA OF " << std::setw(20) << file->getName() << "\n";
    std::cout << "+-------------------------------------------------+\n";

    // Content
    for (const auto& entry : metadata.getMetadata()) {
        std::cout << std::left << std::setw(15) << entry.first 
                    << ": " << std::setw(25) << entry.second << "\n";
    }

    // Footer
    std::cout << "+-------------------------------------------------+\n";
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


