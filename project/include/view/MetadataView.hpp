#ifndef METADATA_VIEW_H
#define METADATA_VIEW_H

#include <string>
#include "BaseView.hpp"
#include "MediaFile.hpp"

enum MetadataMenu {
    BACK_FROM_METADATA,
    SHOW_METADATA,
    EDIT_METADATA
};

class MetadataView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showFileMetadata(const MediaFile& file);
    ~MetadataView() override = default;
};

#endif // METADATA_VIEW_H
