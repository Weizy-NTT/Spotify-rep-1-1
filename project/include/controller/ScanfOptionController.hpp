#ifndef SCANF_OPTION_CONTROLLER_H
#define SCANF_OPTION_CONTROLLER_H

#include <vector>
#include "MediaFile.hpp"

class ScanfOptionController {
public:
    std::vector<MediaFile> scanDirectory(const std::string& path);
    std::vector<MediaFile> scanUSBDevice();
};

#endif // SCANF_OPTION_CONTROLLER_H
