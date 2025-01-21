#ifndef MEDIA_FILE_LIBRARY_H
#define MEDIA_FILE_LIBRARY_H

#include <vector>
#include <memory>
#include <string>
#include "MediaFile.hpp"

class MediaFileLibrary {
private:
    std::vector<std::shared_ptr<MediaFile>> mediaFiles; // Collection of media files in the library

public:
    // Retrieve all media files in the library
    const std::vector<std::shared_ptr<MediaFile>>& getAllMediaFiles() const;

    // Add a new media file to the library
    void addMediaFile(const std::shared_ptr<MediaFile>& files);

    // Remove a media file from the library using its ID
    void removeMediaFile(const std::string& ID);

    // Replace the entire collection of media files in the library
    void setAllMediaFiles(const std::vector<std::shared_ptr<MediaFile>>& files);

    // Retrieve a media file by its unique ID
    std::shared_ptr<MediaFile> getMediaFileByID(const std::string& ID) const;

    // Retrieve a media file by its name
    std::shared_ptr<MediaFile> getMediaFileByName(const std::string& fileName) const;

    // Check if a media file ID exists in the library
    bool isValidMediaFileIDInLibrary(const std::string& ID);

    // Check if a media file name exists in the library
    bool isValidMediaFileNameInLibrary(const std::string& fileName);
};

#endif // MEDIA_FILE_LIBRARY_H
