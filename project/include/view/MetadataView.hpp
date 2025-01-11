#ifndef METADATA_VIEW_H
#define METADATA_VIEW_H

#include <string>
#include "BaseView.hpp"
#include "MediaFile.hpp"
#include <memory>

enum MetadataMenu {
    BACK_FROM_METADATA,
    EDIT_METADATA
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
public:
    void showMenu() override;
    void hideMenu() override;
    void showFileMetadata(const std::shared_ptr<MediaFile>& file);
    void menuEditAudio();
    void menuEditVideo();
    ~MetadataView() override = default;
};

#endif // METADATA_VIEW_H
