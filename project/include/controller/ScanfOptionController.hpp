#ifndef SCANF_OPTION_CONTROLLER_H
#define SCANF_OPTION_CONTROLLER_H

#include <vector>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include <memory>

class ScanfOptionController : public BaseController {
public:
    void handleInput();
    std::vector<std::shared_ptr<MediaFile>> scanDirectory(const std::string& folderPath);
    std::vector<MediaFile> scanUSBDevice();
    void back();
};

#endif // SCANF_OPTION_CONTROLLER_H
