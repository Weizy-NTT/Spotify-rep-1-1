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
#include <unicode/unistr.h>
#include <unicode/translit.h>
#include <unicode/ucnv.h>
#include <unicode/utypes.h>
#include <memory>
#include <stdexcept>
#include <libudev.h>

namespace fs = std::filesystem;

void ScanfOptionController::handleInput(){
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
            std::vector<std::string> devices = scanUSB();
            for (size_t i = 0; i < devices.size();i++) {
                std::cout << i << ". " << devices[i] << std::endl;
            }
            size_t choice;
            Exception_Handler("Enter your path: ",choice,validatePosInteger);
            scanUSBDevice(devices[choice]);
            if (!devices.empty()) {
                scanUSBDevice(devices[choice]);
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
    for (const auto& entry : fs::directory_iterator(device)) {
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
            new_metadata.setValue("Title", removeAccents(tag->title().isEmpty() ? "Unknown" : tag->title().toCString(true)));
            new_metadata.setValue("Artist", removeAccents(tag->artist().isEmpty() ? "Unknown" : tag->artist().toCString(true)));
            new_metadata.setValue("Album", removeAccents(tag->album().isEmpty() ? "Unknown" : tag->album().toCString(true)));
            new_metadata.setValue("Year", tag->year() > 0 ? std::to_string(tag->year()) : "Unknown");
            new_metadata.setValue("Track", tag->track() > 0 ? std::to_string(tag->track()) : "Unknown");
            new_metadata.setValue("Genre", removeAccents(tag->genre().isEmpty() ? "Unknown" : tag->genre().toCString(true)));

            int durationInSeconds = audioProperties->length();
            new_mediafile->setDuration(durationInSeconds);
            std::string duration = (durationInSeconds / 60 < 10 ? "0" : "") + std::to_string(durationInSeconds / 60) + ":" +
                                (durationInSeconds % 60 < 10 ? "0" : "") + std::to_string(durationInSeconds % 60);
            new_metadata.setValue("Duration",duration);
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
            new_metadata.setValue("Title", removeAccents(tag->title().isEmpty() ? "Unknown" : tag->title().toCString(true)));
            new_metadata.setValue("Size", std::to_string(fs::file_size(filePath)));
            int durationInSeconds = audioProperties->length();
            new_mediafile->setDuration(durationInSeconds);
            std::string duration = (durationInSeconds / 60 < 10 ? "0" : "") + std::to_string(durationInSeconds / 60) + ":" +
                                (durationInSeconds % 60 < 10 ? "0" : "") + std::to_string(durationInSeconds % 60);
            new_metadata.setValue("Duration",duration);
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

std::string ScanfOptionController::removeAccents(const std::string& input) {
    try {
        // Khởi tạo UErrorCode
        UErrorCode errorCode = U_ZERO_ERROR;

        // Tạo Transliterator với UErrorCode
        std::unique_ptr<icu::Transliterator> transliterator(
            icu::Transliterator::createInstance(
                icu::UnicodeString::fromUTF8("NFD; [:Nonspacing Mark:] Remove; NFC"),
                UTRANS_FORWARD,
                errorCode
            )
        );

        // Kiểm tra lỗi
        if (U_FAILURE(errorCode)) {
            throw std::runtime_error("Failed to create Transliterator: " + std::string(u_errorName(errorCode)));
        }

        // Chuyển chuỗi từ UTF-8 sang ICU UnicodeString
        icu::UnicodeString unicodeStr = icu::UnicodeString::fromUTF8(input);

        // Áp dụng Transliterator
        transliterator->transliterate(unicodeStr);

        // Chuyển đổi lại UnicodeString sang UTF-8
        std::string output;
        unicodeStr.toUTF8String(output);

        return output;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return input; // Trả về chuỗi gốc nếu có lỗi
    }
}

// Hàm quét USB và trả về vector chứa danh sách các điểm gắn kết USB
std::vector<std::string> ScanfOptionController::scanUSB() {
    std::vector<std::string> usbMountPoints;

    // Lấy tên người dùng hiện tại
    const char* username = getenv("USER");
    if (!username) {
        std::cerr << "Unable to determine username." << std::endl;
        return usbMountPoints;
    }

    // Đường dẫn cơ sở cho các USB
    std::string mediaPath = "/media/";
    mediaPath += username;

    // Kiểm tra nếu thư mục /media/<username> tồn tại
    if (!fs::exists(mediaPath) || !fs::is_directory(mediaPath)) {
        std::cerr << "No USB mount directory found at: " << mediaPath << std::endl;
        return usbMountPoints;
    }

    // Duyệt qua các thư mục trong /media/<username>
    for (const auto& entry : fs::directory_iterator(mediaPath)) {
        if (fs::is_directory(entry.path())) {
            usbMountPoints.push_back(entry.path().string());
        }
    }

    return usbMountPoints;
}