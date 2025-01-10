#ifndef MEDIA_FILE_CONTROLLER_H
#define MEDIA_FILE_CONTROLLER_H

#include <vector>
#include <iostream>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "ControllerManager.hpp"

class MediaFileController : public BaseController {
public:

    void handleInput();
    std::vector<MediaFile> getAllMediaFiles() const;
    void back();
    MediaFile getMediaFileDetails(const std::string& name) const;
};

#endif // MEDIA_FILE_CONTROLLER_H
