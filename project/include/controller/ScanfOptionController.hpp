#ifndef SCANF_OPTION_CONTROLLER_H
#define SCANF_OPTION_CONTROLLER_H

#include <vector>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include <memory>
#include "Playlist.hpp"

class ScanfOptionController : public BaseController {
public:
    void handleInput();
    std::vector<std::shared_ptr<MediaFile>> scanDirectory(const std::string& folderPath);
    std::vector<std::shared_ptr<MediaFile>> scanUSBDevice(const std::string& device);
    void back();
    std::shared_ptr<MediaFile> scanfFilePath(const std::string& filePath);
    void scanPlaylistsFromTxt(const std::string& filePath);
};

#endif // SCANF_OPTION_CONTROLLER_H
