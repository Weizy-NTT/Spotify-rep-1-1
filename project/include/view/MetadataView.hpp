#ifndef METADATA_VIEW_H
#define METADATA_VIEW_H

#include <string>
#include "BaseView.hpp"
#include "MediaFile.hpp"

class MetadataView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void showFileMetadata(const MediaFile& file);
    void editFileMetadata(MediaFile& file);
    void handleInput(const std::string& input) override;
};

#endif // METADATA_VIEW_H
