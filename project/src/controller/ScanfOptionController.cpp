#include "ScanfOptionController.hpp"
#include "ScanfOptionView.hpp"
#include "ControllerManager.hpp"
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <MediaFile.hpp>
#include <cstdlib>

namespace fs = std::filesystem;

void ScanfOptionController::handleInput() {
    ScanStatus status = ScanStatus::SCAN_NORMAL;
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    ControllerManager::getInstance()->getViewManager()->getScanfOptionView()->displayStatusMessage(status);
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_SCANF_VIEW);
    switch (ControllerManager::getInstance()->getViewManager()->getScanfOptionView()->getSelectedOption()) {
        case ScanfMenu::SCANF_DIRECTORY:{
            std::string path;
            Exception_Handler("Enter your path you want to scan: ",path,validatePath);
            scanDirectory(path);
            status = ScanStatus::SCAN_DIRECTORY_SUCCESS;
            break;
        }

        case ScanfMenu::SCANF_USB:{
            std::string device;
            Exception_Handler("Enter your usb device: ",device,validateAlphaSring);
            if (isUSBDevicePresent(device)) {
                scanUSBDevice(device);
                status = ScanStatus::SCAN_USB_SUCCESS;
            }
            else {
                status = ScanStatus::SCAN_USB_FAILURE;
            }
            break;
        }

        case ScanfMenu::BACK_FROM_SCAN:{
            back();
            break;
        }
    }
    } while(ControllerManager::getInstance()->getViewManager()->getScanfOptionView()->getSelectedOption() != ScanfMenu::BACK_FROM_SCAN);
}


void ScanfOptionController::scanDirectory(const std::string& folderPath){
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        auto checkName = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->isValidMediaFileNameInLibrary(entry.path().filename().string());
        if (entry.is_regular_file() && !checkName) {
            std::shared_ptr<MediaFile> mediaFile = scanfFilePath(entry.path().string());
            if (mediaFile) {
                ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->addMediaFile(mediaFile);
            }
        }            
    }
}

void ScanfOptionController::scanUSBDevice(const std::string& device) {
    for (const auto& entry : fs::directory_iterator("/dev/" + device)) {
        auto checkName = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->isValidMediaFileNameInLibrary(entry.path().filename().string());
        if (entry.is_regular_file() && !checkName) {
            std::shared_ptr<MediaFile> mediaFile = scanfFilePath(entry.path().string());
            if (mediaFile) {
                ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->addMediaFile(mediaFile);
            }
        }            
    }
}

void ScanfOptionController::back(){
    //ControllerManager::getInstance()->getMainMenuController()->handleInput();
}

std::shared_ptr<MediaFile> ScanfOptionController::scanfFilePath(const std::string& filePath) {
    namespace fs = std::filesystem;

    if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
        return nullptr;
    }

    std::shared_ptr<MediaFile> new_mediafile = std::make_shared<MediaFile>();
    fs::path path(filePath);

    if (path.extension() == ".mp3") {
        TagLib::FileRef f(filePath.c_str());

        if (!f.isNull() && f.tag() && f.audioProperties()) {
            TagLib::Tag* tag = f.tag();
            TagLib::AudioProperties* audioProperties = f.audioProperties();

            new_mediafile->setName(path.filename().string());
            new_mediafile->setPath(filePath);
            new_mediafile->setType(AUDIO);

            Metadata new_metadata;
            new_metadata.setValue("Title", tag->title().isEmpty() ? "Unknown" : tag->title().toCString(true));
            new_metadata.setValue("Artist", tag->artist().isEmpty() ? "Unknown" : tag->artist().toCString(true));
            new_metadata.setValue("Album", tag->album().isEmpty() ? "Unknown" : tag->album().toCString(true));
            new_metadata.setValue("Year", tag->year() > 0 ? std::to_string(tag->year()) : "Unknown");
            new_metadata.setValue("Track", tag->track() > 0 ? std::to_string(tag->track()) : "Unknown");
            new_metadata.setValue("Genre", tag->genre().isEmpty() ? "Unknown" : tag->genre().toCString(true));


            int durationInSeconds = audioProperties->length();
            new_mediafile->setDuration(durationInSeconds);
            new_metadata.setValue("Duration", std::to_string(durationInSeconds / 60) + ":" + std::to_string(durationInSeconds % 60));
            new_metadata.setValue("Bitrate", std::to_string(audioProperties->bitrate()) + " kbps");
            new_metadata.setValue("SampleRate", std::to_string(audioProperties->sampleRate()) + " Hz");
            new_metadata.setValue("Channels", std::to_string(audioProperties->channels()));

            new_mediafile->setMetadata(new_metadata);
        }
    }
    else if (path.extension() == ".mp4") {
        TagLib::FileRef f(filePath.c_str());

        if (!f.isNull() && f.tag() && f.audioProperties()) {
            TagLib::Tag* tag = f.tag();
            TagLib::AudioProperties* audioProperties = f.audioProperties();

            new_mediafile->setName(path.filename().string());
            new_mediafile->setPath(filePath);
            new_mediafile->setType(VIDEO);

            Metadata new_metadata;
            new_metadata.setValue("Title", tag->title().isEmpty() ? "Unknown" : tag->title().toCString(true));
            new_metadata.setValue("Size", std::to_string(fs::file_size(filePath)));
            int durationInSeconds = audioProperties->length();
            new_mediafile->setDuration(durationInSeconds);
            new_metadata.setValue("Duration", std::to_string(durationInSeconds / 60) + ":" + std::to_string(durationInSeconds % 60));
            new_metadata.setValue("Bitrate", std::to_string(audioProperties->bitrate()) + " kbps");

            new_mediafile->setMetadata(new_metadata);
        }
    } else {
        return nullptr;
    }

    return new_mediafile;
} 

void ScanfOptionController::scanPlaylistsFromTxt(const std::string& filePath) {
    if (!ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getAllPlaylists().empty()) {
        return;
    }

    std::vector<std::shared_ptr<Playlist>> playlists;
    std::ifstream inFile(filePath);

    if (!inFile) {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return;
    }

    std::string line;
    std::shared_ptr<Playlist> currentPlaylist = nullptr;

    while (std::getline(inFile, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            if (currentPlaylist) {
                playlists.push_back(currentPlaylist);
                currentPlaylist = nullptr;
            }
            continue;
        }

        if (line.find("/") == std::string::npos) {
            if (currentPlaylist) {
                playlists.push_back(currentPlaylist);
            }
            currentPlaylist = std::make_shared<Playlist>(line);
        } else if (currentPlaylist) {
            if (!std::filesystem::exists(line)) {
                std::cerr << "File not found: " << line << "\n";
                continue;
            }
            size_t pos = line.find_last_of("/");
            std::string filename = line.substr(pos + 1);

            auto checkName = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->isValidMediaFileNameInLibrary(filename);
            if (!checkName) {
                std::shared_ptr<MediaFile> new_mediafile = scanfFilePath(line);
                currentPlaylist->addSong(new_mediafile);
                ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->addMediaFile(new_mediafile);              
            }
            else {
                std::shared_ptr<MediaFile> new_mediafile = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByName(filename);
                currentPlaylist->addSong(new_mediafile);
            }
        }
    }

    if (currentPlaylist) {
        playlists.push_back(currentPlaylist);
    }

    inFile.close();

    for (auto playlist : playlists) {
        ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->addPlaylist(playlist);
    }

}