#ifndef MEDIA_FILE_LIBRARY_H
#define MEDIA_FILE_LIBRARY_H

#include <vector>
#include "MediaFile.hpp"

class MediaFileLibrary {
private:
    std::vector<MediaFile> mediaFiles;

public:
    std::vector<MediaFile> getAllMediaFiles() const;
    void addMediaFile(const MediaFile& file);
    void removeMediaFile(const MediaFile& file);
    MediaFile getMediaFileByName(const std::string& name) const;
    void scanDirectory(const std::string& path);
    void scanUSBDevice();
};

#endif // MEDIA_FILE_LIBRARY_H