#include "MetadataController.hpp"
#include "ControllerManager.hpp"
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <filesystem>

namespace fs = std::filesystem;

void MetadataController::handleInput(const std::string& ID){
    size_t mainChoice;
    MediaType type = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getType();
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    getMediaFileMetadata(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID));
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_METADATA_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validateMetadataMenu);
    switch (mainChoice)
        {
            case MetadataMenu::BACK_FROM_METADATA: {
                back();
                break;
            }
            case MetadataMenu::EDIT_METADATA:{
                if (type == AUDIO) {
                    ControllerManager::getInstance()->getViewManager()->getMetadataView()->menuEditAudio();
                    handleEditAudio(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getPath(),ID);
                }
                else {
                    ControllerManager::getInstance()->getViewManager()->getMetadataView()->menuEditVideo();
                    handleEditVideo(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getPath(),ID);
                }
                break;
            }
        }
    } while(mainChoice != MetadataMenu::BACK_FROM_METADATA);
}

void MetadataController::getMediaFileMetadata(const std::shared_ptr<MediaFile>& file) const{
    ControllerManager::getInstance()->getViewManager()->getMetadataView()->showFileMetadata(file);
}

void MetadataController::updateMediaFileMetadata(const std::string& key, const std::string& value,const std::string& ID){
    ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getMetadata().setValue(key,value);
}
void MetadataController::back(){
    
}

void MetadataController::handleEditAudio(const std::string& filepath,const std::string& ID) {
    size_t editChoice;
    std::string newValue;
    TagLib::FileRef f(filepath.c_str());

    if (!f.isNull() && f.tag() && f.audioProperties()) {
    TagLib::Tag* tag = f.tag();
    //TagLib::AudioProperties* audioProperties = f.audioProperties();
    do {
        Exception_Handler("Enter your choice: ",editChoice,validateEditAudioMenu);
        switch(editChoice)
        {
            case AudioEdit::AUDIO_BACK: {
                back();
                break;
            }
            case AudioEdit::AUDIO_TITLE: {
                Exception_Handler("Enter new title: ",newValue,validateAlphaSring);
                tag->setTitle(TagLib::String(newValue));
                updateMediaFileMetadata("Title",newValue,ID);
                break;
            }
            case AudioEdit::AUDIO_ARTIST: {
                Exception_Handler("Enter new artist: ",newValue,validateAlphaSring);
                tag->setArtist(TagLib::String(newValue));
                updateMediaFileMetadata("Artist",newValue,ID);
                break;
            }
            case AudioEdit::AUDIO_ALBUM: {
                Exception_Handler("Enter new album: ",newValue,validateAlphaSring);
                tag->setAlbum(TagLib::String(newValue));
                updateMediaFileMetadata("Album",newValue,ID);
                break;
            }
            case AudioEdit::AUDIO_YEAR: {
                Exception_Handler("Enter new year: ",newValue,validateYear);
                tag->setYear(std::stoi(newValue));
                updateMediaFileMetadata("Year",newValue,ID);
                break;
            }
            case AudioEdit::AUDIO_TRACK: {
                Exception_Handler("Enter new track: ",newValue,validateTrack);
                tag->setTrack(std::stoi(newValue));
                updateMediaFileMetadata("Track",newValue,ID);
                break;
            }
            case AudioEdit::AUDIO_GENRE: {
                Exception_Handler("Enter new genre: ",newValue,validateAlphaSring);
                tag->setGenre(TagLib::String(newValue));
                updateMediaFileMetadata("Genre",newValue,ID);
                break;
            }
            default:
                std::cout << "Invalid input\n";
        }
    } while(editChoice != AudioEdit::AUDIO_BACK);

    if (f.save()) {
        std::cout << "\nMetadata updated successfully\n" << std::endl;
    } else {
        std::cerr << "Error: Could not save changes to the file." << std::endl;
    }
    }
    else {
        std::cerr << "Error: Could not open file or retrieve metadata for " << filepath << std::endl;
    }
}

void MetadataController::handleEditVideo(const std::string& filepath,const std::string& ID) {
    size_t editChoice;
    std::string newValue;
    TagLib::FileRef f(filepath.c_str());

    if (!f.isNull() && f.tag() && f.audioProperties()) {
    TagLib::Tag* tag = f.tag();
    //TagLib::AudioProperties* audioProperties = f.audioProperties();
    do {
        Exception_Handler("Enter your choice: ",editChoice,validateEditVideoMenu);
        switch(editChoice)
        {
            case VideoEdit::VIDEO_BACK: {
                back();
                break;
            }
            case VideoEdit::VIDEO_TITLE: {
                Exception_Handler("Enter new title: ",newValue,validateAlphaSring);
                tag->setTitle(TagLib::String(newValue));
                updateMediaFileMetadata("Title",newValue,ID);
                break;
            }
            default:
                std::cout << "Invalid input\n";
        }
    } while(editChoice != AudioEdit::AUDIO_BACK);
    
    if (f.save()) {
        std::cout << "\nMetadata updated successfully\n" << std::endl;
    } else {
        std::cerr << "Error: Could not save changes to the file." << std::endl;
    }
    }
    else {
        std::cerr << "Error: Could not open file or retrieve metadata for " << filepath << std::endl;
    }
}
