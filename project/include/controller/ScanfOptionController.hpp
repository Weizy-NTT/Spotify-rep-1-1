#ifndef SCANF_OPTION_CONTROLLER_H
#define SCANF_OPTION_CONTROLLER_H

#include <vector>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include <memory>
#include "Playlist.hpp"

class ScanfOptionController : public BaseController {
private:
    // Remove accents from the input string (e.g., for normalization)
    std::string removeAccents(const std::string& input);

public:
    // Handle user input for scanning options
    void handleInput();

    // Scan media files from a specified directory
    void scanDirectory(const std::string& folderPath);

    // Scan media files from a USB device
    void scanUSBDevice(const std::string& device);

    // Navigate back to the previous menu or screen
    void back();

    // Scan a single media file from the given file path
    std::shared_ptr<MediaFile> scanfFilePath(const std::string& filePath);

    // Scan playlists from a text file at the specified path
    void scanPlaylistsFromTxt(const std::string& filePath);
    std::vector<std::string> scanUSB();
};

#endif // SCANF_OPTION_CONTROLLER_H
