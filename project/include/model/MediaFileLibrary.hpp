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
    void setAllMediaFiles(const std::vector<MediaFile> files);
    MediaFile getMediaFileByName(const std::string& name) const;
};

#endif // MEDIA_FILE_LIBRARY_H