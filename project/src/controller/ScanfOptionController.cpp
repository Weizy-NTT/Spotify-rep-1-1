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

void ScanfOptionController::handleInput(){
    ScanStatus status = ScanStatus::SCAN_NORMAL;
    size_t mainChoice;
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    ControllerManager::getInstance()->getViewManager()->getScanfOptionView()->displayStatusMessage(status);
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_SCANF_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validateScanfMenu);
    switch (mainChoice)
        {
        case ScanfMenu::BACK_FROM_SCAN: {
            back();
            break;
        }
        case ScanfMenu::SCANF_DIRECTORY:{
            std::string path;
            Exception_Handler("Enter your path you want to scan: ",path,validatePath);
            ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->setAllMediaFiles(scanDirectory(path));
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
        }
    } while(mainChoice != ScanfMenu::BACK_FROM_SCAN);
}

std::vector<std::shared_ptr<MediaFile>> ScanfOptionController::scanDirectory(const std::string& folderPath){
    std::vector<std::shared_ptr<MediaFile>> songList;
    unsigned int count = 0;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::shared_ptr<MediaFile> mediaFile = scanfFilePath(entry.path().string());
            if (mediaFile) {
                count++;
                mediaFile->setID(std::to_string(count));
                songList.push_back(mediaFile);
            }
        }            
    }
    return songList;
}

std::vector<std::shared_ptr<MediaFile>> ScanfOptionController::scanUSBDevice(const std::string& device) {
    std::vector<std::shared_ptr<MediaFile>> songList;
    unsigned int count = 0;

    for (const auto& entry : fs::directory_iterator("/dev/" + device)) {
        if (entry.is_regular_file()) {
            std::shared_ptr<MediaFile> mediaFile = scanfFilePath(entry.path().string());
            if (mediaFile) {
                count++;
                mediaFile->setID(std::to_string(count));
                songList.push_back(mediaFile);
            }
        }            
    }
    return songList;
}

void ScanfOptionController::back(){
    //nothing
}

std::shared_ptr<MediaFile> ScanfOptionController::scanfFilePath(const std::string& filePath) {
    namespace fs = std::filesystem;

    // Kiểm tra nếu đường dẫn không tồn tại hoặc không phải là file
    if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
        return nullptr;
    }

    std::shared_ptr<MediaFile> new_mediafile = std::make_shared<MediaFile>();
    fs::path path(filePath);

    // Kiểm tra định dạng file .mp3
    if (path.extension() == ".mp3") {
        TagLib::FileRef f(filePath.c_str());

        if (!f.isNull() && f.tag() && f.audioProperties()) {
            TagLib::Tag* tag = f.tag();
            TagLib::AudioProperties* audioProperties = f.audioProperties();

            new_mediafile->setName(path.filename().string());
            new_mediafile->setPath(filePath);
            new_mediafile->setType(AUDIO);

            Metadata new_metadata;
            new_metadata.setValue("Title", tag->title().toCString(true));
            new_metadata.setValue("Artist", tag->artist().toCString(true));
            new_metadata.setValue("Album", tag->album().toCString(true));
            new_metadata.setValue("Year", std::to_string(tag->year()));
            new_metadata.setValue("Track", std::to_string(tag->track()));
            new_metadata.setValue("Genre", tag->genre().toCString(true));

            int durationInSeconds = audioProperties->length();
            int minutes = durationInSeconds / 60;
            int seconds = durationInSeconds % 60;
            std::string durationFormatted = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
            new_metadata.setValue("Duration", durationFormatted);

            new_metadata.setValue("Channels", std::to_string(audioProperties->channels()));
            new_metadata.setValue("Sample Rate", std::to_string(audioProperties->sampleRate()) + " Hz");
            new_metadata.setValue("Bitrate", std::to_string(audioProperties->bitrate()) + " kbps");

            new_mediafile->setMetadata(new_metadata);
        }
    }
    // Kiểm tra định dạng file .mp4
    else if (path.extension() == ".mp4") {
        TagLib::FileRef f(filePath.c_str());

        if (!f.isNull() && f.tag() && f.audioProperties()) {
            TagLib::Tag* tag = f.tag();
            TagLib::AudioProperties* audioProperties = f.audioProperties();

            new_mediafile->setName(path.filename().string());
            std::string wavFilePath = extractAudio(filePath);
            if (!wavFilePath.empty()) {
                new_mediafile->setPath(wavFilePath);
            }
            new_mediafile->setType(VIDEO);

            Metadata new_metadata;
            new_metadata.setValue("Title", tag->title().toCString(true));
            new_metadata.setValue("Size", std::to_string(fs::file_size(filePath)));

            int durationInSeconds = audioProperties->length();
            int minutes = durationInSeconds / 60;
            int seconds = durationInSeconds % 60;
            std::string durationFormatted = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
            new_metadata.setValue("Duration", durationFormatted);

            new_metadata.setValue("Bitrate", std::to_string(audioProperties->bitrate()) + " kbps");

            new_mediafile->setMetadata(new_metadata);
        }
    } else {
        return nullptr;
    }

    return new_mediafile;
}

std::string ScanfOptionController::extractAudio(const std::string &videoPath) {
    // Đường dẫn folder cho các file .wav
    std::string outputFolderPath = "./resources/musicfrommp4";
    // Tên file đầu ra 
    std::string outputAudioPath = outputFolderPath + "/" + fs::path(videoPath).stem().string() + ".wav";
    std::string command = "ffmpeg -i \"" + videoPath + "\" -q:a 0 -map a \"" + outputAudioPath + "\" -y";

    // Kiểm tra và tạo folder nếu chưa tồn tại
    if(!fs::exists(outputFolderPath)){
        fs::create_directories(outputFolderPath);
    }

    if (fs::exists(outputAudioPath)) {
        std::cout << "Audio file already exists: " << outputAudioPath << "\n";
        return outputAudioPath;
    }
    
    // Thực thi lệnh ffmpeg
    int result = system(command.c_str());
    if(result != 0){
        std::cerr << "Failed to extract audio using FFmpeg.\n";
        return "";
    }

    std::cout <<  "Audio extracted to: " << outputAudioPath << "\n";
    return outputAudioPath;
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

            auto new_mediafile = std::make_shared<MediaFile>();
            new_mediafile->setPath(line);
            new_mediafile->setName(std::filesystem::path(line).filename().string());

            size_t fileIndex = 1;
            try {
                for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::path(line).parent_path())) {
                    if (entry.path() == line) {
                        break;
                    }
                    fileIndex++;
                }
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Error accessing folder: " << e.what() << "\n";
            }

            new_mediafile->setID(std::to_string(fileIndex));

            TagLib::FileRef f(line.c_str());
            Metadata metadata;

            if (!f.isNull() && f.tag() && f.audioProperties()) {
                TagLib::Tag* tag = f.tag();
                TagLib::AudioProperties* audioProperties = f.audioProperties();

                metadata.setValue("Title", tag->title().isEmpty() ? "Unknown" : tag->title().toCString(true));
                metadata.setValue("Artist", tag->artist().isEmpty() ? "Unknown" : tag->artist().toCString(true));
                metadata.setValue("Album", tag->album().isEmpty() ? "Unknown" : tag->album().toCString(true));
                metadata.setValue("Year", tag->year() > 0 ? std::to_string(tag->year()) : "Unknown");

                int durationInSeconds = audioProperties->length();
                metadata.setValue("Duration", std::to_string(durationInSeconds / 60) + ":" + std::to_string(durationInSeconds % 60));
                metadata.setValue("Bitrate", std::to_string(audioProperties->bitrate()) + " kbps");
                metadata.setValue("SampleRate", std::to_string(audioProperties->sampleRate()) + " Hz");
                metadata.setValue("Channels", std::to_string(audioProperties->channels()));

                new_mediafile->setType(line.find(".mp4") != std::string::npos ? VIDEO : AUDIO);
            } else {
                metadata.setValue("Title", "Unknown");
                metadata.setValue("Artist", "Unknown");
                metadata.setValue("Album", "Unknown");
                metadata.setValue("Year", "Unknown");
                metadata.setValue("Duration", "Unknown");
                metadata.setValue("Bitrate", "Unknown");
                metadata.setValue("SampleRate", "Unknown");
                metadata.setValue("Channels", "Unknown");
                new_mediafile->setType(UNKNOWN);
            }

            ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->addMediaFile(new_mediafile);
            new_mediafile->setMetadata(metadata);
            currentPlaylist->addSong(new_mediafile);
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