#ifndef MEDIA_FILE_CONTROLLER_H
#define MEDIA_FILE_CONTROLLER_H

#include <vector>
#include <iostream>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "memory"

class MediaFileController : public BaseController {
private:
    int currentPage = 1;
public:
    void handleInput();
    std::vector<MediaFile> getAllMediaFiles() const;
    void back();
    MediaFile getMediaFileDetails(const std::string& name) const;
    void displayMediaFilesWithPagination(const std::vector<std::shared_ptr<MediaFile>>& files, int pageSize = 25);
};

#endif // MEDIA_FILE_CONTROLLER_H
