#ifndef MEDIA_FILE_LIBRARY_H
#define MEDIA_FILE_LIBRARY_H

#include <vector>
#include <memory>
#include <string>
#include "MediaFile.hpp"

class MediaFileLibrary {
private:
    std::vector<std::shared_ptr<MediaFile>> mediaFiles;

public:
    const std::vector<std::shared_ptr<MediaFile>>& getAllMediaFiles() const;
    void addMediaFile(const std::shared_ptr<MediaFile>& files);
    void removeMediaFile(const std::string& ID);
    void setAllMediaFiles(const std::vector<std::shared_ptr<MediaFile>>& files);
    std::shared_ptr<MediaFile> getMediaFileByID(const std::string& ID) const;
    bool isValidMediaFileIDInLibrary(const std::string& ID);
};

#endif // MEDIA_FILE_LIBRARY_H
