#ifndef MEDIA_FILE_CONTROLLER_H
#define MEDIA_FILE_CONTROLLER_H

#include <vector>
#include <iostream>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "memory"

class MediaFileController : public BaseController {
private:
    size_t currentPage = 1; // The current page being displayed

public:
    // Handle user input for media file operations
    void handleInput();

    // Navigate back to the previous menu or screen
    void back();

    // Display media files with pagination
    // Parameters:
    // - files: A vector of shared pointers to MediaFile objects
    // - pageSize: The number of items to display per page (default is 25)
    void displayMediaFilesWithPagination(const std::vector<std::shared_ptr<MediaFile>>& files, size_t pageSize = 25);
};

#endif // MEDIA_FILE_CONTROLLER_H
