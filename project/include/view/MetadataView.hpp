#ifndef METADATA_VIEW_H
#define METADATA_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>
#include "MediaFile.hpp"
#include <memory>

enum MetadataMenu {
    EDIT_METADATA,
    BACK_FROM_METADATA
};

enum AudioEdit {
    AUDIO_BACK,
    AUDIO_TITLE,
    AUDIO_ARTIST,
    AUDIO_ALBUM,
    AUDIO_YEAR,
    AUDIO_TRACK,
    AUDIO_GENRE,
};

enum VideoEdit {
    VIDEO_BACK,
    VIDEO_TITLE
};

class MetadataView : public BaseView {
private:
    std::vector<std::string> menu_entries = {
        "Edit File Metadata",
        "Go Back"
    };
    int selected_option = 0;

public:
    void showMenu() override;
    int getSelectedOption() const;
    ~MetadataView() override = default;
    void hideMenu() override;
    void showFileMetadata(const std::shared_ptr<MediaFile>& file);
    void menuEditAudio();
    void menuEditVideo();
};

#endif // METADATA_VIEW_H
