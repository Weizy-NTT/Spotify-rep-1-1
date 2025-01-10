#include "ScanfOptionController.hpp"
#include <iostream>
#include "ScanfOptionView.hpp"
#include "ControllerManager.hpp"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <MediaFile.hpp>

namespace fs = std::filesystem;

void ScanfOptionController::handleInput(){
    size_t mainChoice;
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
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
            std::cout<<"Enter your path you want to scan: ";
            std::getline(std::cin, path);
            ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->setAllMediaFiles(scanDirectory(path));
            break;
        }
           
        case ScanfMenu::SCANF_USB:{
            std::string path;
            std::cout<<"Enter your path you want to scan from usb: ";
            std::getline(std::cin, path);
            scanDirectory(path);
            break;
        }
        }
    } while(mainChoice != ScanfMenu::BACK_FROM_SCAN);
}

std::vector<std::shared_ptr<MediaFile>> ScanfOptionController::scanDirectory(const std::string& folderPath){
    std::vector<std::shared_ptr<MediaFile>> songList;
    unsigned int count = 0;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            TagLib::FileRef f(entry.path().c_str());

            if (!f.isNull() && f.tag() && f.audioProperties()) {
                TagLib::Tag* tag = f.tag();
                TagLib::AudioProperties* audioProperties = f.audioProperties();

                count++;
                std::string ID = std::to_string(count);
                std::shared_ptr<MediaFile> new_mediafile = std::make_shared<MediaFile>();
                new_mediafile->setID(ID);
                new_mediafile->setName(entry.path().filename().string());
                new_mediafile->setPath(entry.path().string());
                new_mediafile->setType(AUDIO);

                Metadata new_metadata;
                new_metadata.setValue("Title",tag->title().toCString(true));
                new_metadata.setValue("Artist",tag->artist().toCString(true));
                new_metadata.setValue("Album",tag->album().toCString(true));
                // Convert year from unsigned int to string
                std::string yearString = std::to_string(tag->year());
                new_metadata.setValue("Year",yearString);
                // Convert track from unsigned int to string
                std::string trackString = std::to_string(tag->track());                
                new_metadata.setValue("Track", trackString);
                new_metadata.setValue("Genre",tag->genre().toCString(true));
                // Convert and set the duration
                int durationInSeconds = audioProperties->length();
                int minutes = durationInSeconds / 60;
                int seconds = durationInSeconds % 60;
                std::string durationFormatted = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
                new_metadata.setValue("Duration", durationFormatted);
                // Convert channels to string
                std::string channels = std::to_string(audioProperties->channels());
                new_metadata.setValue("Channels", channels);
                // Convert sample rate to string
                std::string sampleRate = std::to_string(audioProperties->sampleRate()) + " Hz";
                new_metadata.setValue("Sample Rate", sampleRate);
                // Convert bitrate to string
                std::string bitrate = std::to_string(audioProperties->bitrate()) + " kbps";
                new_metadata.setValue("Bitrate", bitrate);
                new_mediafile->setMetadata(new_metadata);
                songList.push_back(new_mediafile);
            }
        }
        else if(entry.is_regular_file() && entry.path().extension() == ".mp4") {
            fs::path file_path = entry.path();
                TagLib::FileRef f(entry.path().c_str());
            if (!f.isNull() && f.tag() && f.audioProperties()) {
                TagLib::Tag* tag = f.tag();
                TagLib::AudioProperties* audioProperties = f.audioProperties();

                count++;
                std::string ID = std::to_string(count);
                std::shared_ptr<MediaFile> new_videofile = std::make_shared<MediaFile>();
                new_videofile->setID(ID);
                new_videofile->setName(entry.path().filename().string());
                new_videofile->setPath(entry.path().string());
                new_videofile->setType(VIDEO);

                Metadata new_metadata;
                new_metadata.setValue("Tittle", tag->title().toCString(true));
                new_metadata.setValue("Size", std::to_string(fs::file_size(entry.path())));
                // Convert and set the duration
                int durationInSeconds = audioProperties->length();
                int minutes = durationInSeconds / 60;
                int seconds = durationInSeconds % 60;
                std::string durationFormatted = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
                new_metadata.setValue("Duration", durationFormatted);
                // Convert bitrate to string
                std::string bitrate = std::to_string(audioProperties->bitrate()) + " kbps";
                new_metadata.setValue("Bitrate", bitrate);
                //codec
                new_videofile->setMetadata(new_metadata);
                songList.push_back(new_videofile);
            }
        }            
    }
    return songList;
}

// std::vector<MediaFile> ScanfOptionController::scanUSBDevice(){

// }

void ScanfOptionController::back(){
    //nothing
}