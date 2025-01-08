#ifndef MEDIA_FILE_CONTROLLER_H
#define MEDIA_FILE_CONTROLLER_H

#include <vector>
#include "MediaFile.hpp"
#include "BaseController.hpp"

class MediaFileController : public BaseController {
public:
    void inputFromKeyboard();
    void handleInput(const std::string& input);
    std::vector<MediaFile> getAllMediaFiles() const;
    MediaFile getMediaFileDetails(const std::string& name) const;
};

#endif // MEDIA_FILE_CONTROLLER_H
