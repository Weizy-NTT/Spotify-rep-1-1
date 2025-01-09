#ifndef MEDIA_FILE_CONTROLLER_H
#define MEDIA_FILE_CONTROLLER_H

#include <vector>
#include <iostream>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "MediaFileView.hpp"
#include "ControllerManager.hpp"

class MediaFileController : public BaseController {
public:
    void inputFromKeyboard();
    void handleInput(const size_t & input);
    std::vector<MediaFile> getAllMediaFiles() const;
    void back();
    MediaFile getMediaFileDetails(const std::string& name) const;
};

#endif // MEDIA_FILE_CONTROLLER_H
