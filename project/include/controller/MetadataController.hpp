#ifndef METADATA_CONTROLLER_H
#define METADATA_CONTROLLER_H

#include <map>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include <memory>

class MetadataController : public BaseController {
public:
    // Handle user input for a specific media file by its ID
    void handleInput(const std::string& ID);

    // Retrieve and display metadata of a given media file
    void getMediaFileMetadata(const std::shared_ptr<MediaFile>& file) const;

    // Update metadata of a media file based on key-value pairs and its ID
    void updateMediaFileMetadata(const std::string& key, const std::string& value, const std::string& ID);

    // Navigate back to the previous menu or screen
    void back();

    // Handle editing audio metadata for the given file path and ID
    void handleEditAudio(const std::string& filepath, const std::string& ID);

    // Handle editing video metadata for the given file path and ID
    void handleEditVideo(const std::string& filepath, const std::string& ID);
};

#endif // METADATA_CONTROLLER_H
