#include "MetadataController.hpp"
#include "ControllerManager.hpp"
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <filesystem>

namespace fs = std::filesystem;

// Handle user input for editing metadata
void MetadataController::handleInput(const std::string& ID) {
    MediaType type = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getType();
    do {
        // Hide the current view and display metadata of the selected file
        ControllerManager::getInstance()->getViewManager()->hideCurrentView();
        getMediaFileMetadata(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID));

        // Switch to the metadata view
        ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_METADATA_VIEW);

        // Handle user input based on the selected metadata menu option
        switch (ControllerManager::getInstance()->getViewManager()->getMetadataView()->getSelectedOption()) {
            case MetadataMenu::BACK_FROM_METADATA: {
                back();
                break;
            }
            case MetadataMenu::EDIT_METADATA: {
                // Handle editing based on file type (audio or video)
                if (type == AUDIO) {
                    handleEditAudio(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getPath(), ID);
                } else {
                    handleEditVideo(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getPath(), ID);
                }
                break;
            }
        }
    } while (ControllerManager::getInstance()->getViewManager()->getMetadataView()->getSelectedOption() != MetadataMenu::BACK_FROM_METADATA);
}

// Retrieve and display metadata of the given media file
void MetadataController::getMediaFileMetadata(const std::shared_ptr<MediaFile>& file) const {
    ControllerManager::getInstance()->getViewManager()->getMetadataView()->showFileMetadata(file);
}

// Update the metadata of the specified media file
void MetadataController::updateMediaFileMetadata(const std::string& key, const std::string& value, const std::string& ID) {
    ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getMetadata().setValue(key, value);
}

// Handle the back navigation logic
void MetadataController::back() {
    // Placeholder for back navigation logic
}

void MetadataController::handleEditAudio(const std::string& filepath, const std::string& ID) {
    std::string newValue;
    TagLib::FileRef f(filepath.c_str()); // Create a TagLib::FileRef object to access metadata.

    // Check if the file is valid and contains metadata and audio properties.
    if (!f.isNull() && f.tag() && f.audioProperties()) {
        TagLib::Tag* tag = f.tag(); // Access the tag metadata.

        // Enter a loop for editing audio metadata options.
        do {
            // Hide the current view and display metadata details.
            ControllerManager::getInstance()->getViewManager()->hideCurrentView();
            getMediaFileMetadata(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID));
            ControllerManager::getInstance()->getViewManager()->getMetadataView()->menuEditAudio();

            // Handle user input for different audio metadata fields.
            switch (ControllerManager::getInstance()->getViewManager()->getMetadataView()->getAuditoOption()) {
                case AudioEdit::AUDIO_BACK: {
                    back(); // Exit the loop and return to the previous menu.
                    break;
                }
                case AudioEdit::AUDIO_TITLE: {
                    Exception_Handler("Enter new title: ", newValue, validateAlphaSring); // Get and validate user input.
                    tag->setTitle(TagLib::String(newValue)); // Update the title in the metadata.
                    updateMediaFileMetadata("Title", newValue, ID); // Update metadata in the model.
                    break;
                }
                case AudioEdit::AUDIO_ARTIST: {
                    Exception_Handler("Enter new artist: ", newValue, validateAlphaSring); // Get and validate user input.
                    tag->setArtist(TagLib::String(newValue)); // Update the artist in the metadata.
                    updateMediaFileMetadata("Artist", newValue, ID); // Update metadata in the model.
                    break;
                }
                case AudioEdit::AUDIO_ALBUM: {
                    Exception_Handler("Enter new album: ", newValue, validateAlphaSring); // Get and validate user input.
                    tag->setAlbum(TagLib::String(newValue)); // Update the album in the metadata.
                    updateMediaFileMetadata("Album", newValue, ID); // Update metadata in the model.
                    break;
                }
                case AudioEdit::AUDIO_YEAR: {
                    Exception_Handler("Enter new year: ", newValue, validateYear); // Get and validate user input.
                    tag->setYear(std::stoi(newValue)); // Update the year in the metadata.
                    updateMediaFileMetadata("Year", newValue, ID); // Update metadata in the model.
                    break;
                }
                case AudioEdit::AUDIO_TRACK: {
                    Exception_Handler("Enter new track: ", newValue, validateTrack); // Get and validate user input.
                    tag->setTrack(std::stoi(newValue)); // Update the track number in the metadata.
                    updateMediaFileMetadata("Track", newValue, ID); // Update metadata in the model.
                    break;
                }
                case AudioEdit::AUDIO_GENRE: {
                    Exception_Handler("Enter new genre: ", newValue, validateAlphaSring); // Get and validate user input.
                    tag->setGenre(TagLib::String(newValue)); // Update the genre in the metadata.
                    updateMediaFileMetadata("Genre", newValue, ID); // Update metadata in the model.
                    break;
                }
                default:
                    std::cout << "Invalid input\n"; // Handle invalid input.
            }
        } while (ControllerManager::getInstance()->getViewManager()->getMetadataView()->getAuditoOption() != AudioEdit::AUDIO_BACK);
        f.save(); // Save the updated metadata back to the file.
    } else {
        // Handle cases where the file cannot be opened or metadata is not available.
        std::cerr << "Error: Could not open file or retrieve metadata for " << filepath << std::endl;
    }
}

void MetadataController::handleEditVideo(const std::string& filepath, const std::string& ID) {
    std::string newValue;
    TagLib::FileRef f(filepath.c_str()); // Create a TagLib::FileRef object to access metadata.

    // Check if the file is valid and contains metadata and audio properties.
    if (!f.isNull() && f.tag() && f.audioProperties()) {
        TagLib::Tag* tag = f.tag(); // Access the tag metadata.

        // Enter a loop for editing video metadata options.
        do {
            // Hide the current view and display metadata details.
            ControllerManager::getInstance()->getViewManager()->hideCurrentView();
            getMediaFileMetadata(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID));
            ControllerManager::getInstance()->getViewManager()->getMetadataView()->menuEditVideo();

            // Handle user input for different video metadata fields.
            switch (ControllerManager::getInstance()->getViewManager()->getMetadataView()->getVideoOption()) {
                case VideoEdit::VIDEO_BACK: {
                    back(); // Exit the loop and return to the previous menu.
                    break;
                }
                case VideoEdit::VIDEO_TITLE: {
                    Exception_Handler("Enter new title: ", newValue, validateAlphaSring); // Get and validate user input.
                    tag->setTitle(TagLib::String(newValue)); // Update the title in the metadata.
                    updateMediaFileMetadata("Title", newValue, ID); // Update metadata in the model.
                    break;
                }
                default:
                    std::cout << "Invalid input\n"; // Handle invalid input.
            }
        } while (ControllerManager::getInstance()->getViewManager()->getMetadataView()->getVideoOption() != VideoEdit::VIDEO_BACK);
        f.save(); // Save the updated metadata back to the file.
    } else {
        // Handle cases where the file cannot be opened or metadata is not available.
        std::cerr << "Error: Could not open file or retrieve metadata for " << filepath << std::endl;
    }
}
