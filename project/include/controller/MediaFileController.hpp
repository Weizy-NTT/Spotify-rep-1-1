#ifndef MEDIA_FILE_CONTROLLER_H
#define MEDIA_FILE_CONTROLLER_H

#include <vector>
#include "MediaFile.hpp"

class MediaFileController {
public:
    std::vector<MediaFile> getAllMediaFiles() const;
    MediaFile getMediaFileDetails(const std::string& name) const;
};

#endif // MEDIA_FILE_CONTROLLER_H
