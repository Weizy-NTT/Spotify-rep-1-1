#ifndef METADATA_VIEW_H
#define METADATA_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>
#include "MediaFile.hpp"
#include <memory>

// Enum for metadata menu options
enum MetadataMenu {
    EDIT_METADATA,        // Option to edit file metadata
    BACK_FROM_METADATA    // Option to go back to the previous menu
};

// Enum for audio metadata editing options
enum AudioEdit {
    AUDIO_TITLE,
    AUDIO_ARTIST,
    AUDIO_ALBUM,
    AUDIO_YEAR,
    AUDIO_TRACK,
    AUDIO_GENRE,
    AUDIO_BACK
};

// Enum for video metadata editing options
enum VideoEdit {
    VIDEO_TITLE,
    VIDEO_BACK
};

class MetadataView : public BaseView {
private:
    // Menu entries for the metadata view
    std::vector<std::string> menu_entries = {
        "Edit File Metadata",
        "Go Back"
    };
    int selected_option = 0;
    int selected_option_audio = 0;        
    int selected_option_video = 0;
public:
    // Override to display the menu
    void showMenu() override;

    // Getter to retrieve the user's selected option
    int getSelectedOption() const;
    int getAuditoOption() const;
    int getVideoOption() const;
    ~MetadataView() override = default;

    // Override to hide the menu
    void hideMenu() override;

    // Display the metadata of the specified media file
    void showFileMetadata(const std::shared_ptr<MediaFile>& file);

    // Display the menu for editing audio metadata
    void menuEditAudio();

    // Display the menu for editing video metadata
    void menuEditVideo();
};

#endif // METADATA_VIEW_H
