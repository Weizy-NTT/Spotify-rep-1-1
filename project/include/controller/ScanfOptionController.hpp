#ifndef SCANF_OPTION_CONTROLLER_H
#define SCANF_OPTION_CONTROLLER_H

#include <vector>
#include "MediaFile.hpp"
#include "BaseController.hpp"

class ScanfOptionController : public BaseController {
public:
    void handleInput();
    std::vector<MediaFile> scanDirectory(const std::string& path);
    std::vector<MediaFile> scanUSBDevice();
    void back();
};

#endif // SCANF_OPTION_CONTROLLER_H
