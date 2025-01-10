#ifndef METADATA_CONTROLLER_H
#define METADATA_CONTROLLER_H

#include <map>
#include "MediaFile.hpp"
#include "BaseController.hpp"
#include "ControllerManager.hpp"

class MetadataController : public BaseController {
public:
    void handleInput(const std::string& ID);
    std::map<std::string, std::string> getMediaFileMetadata(const MediaFile& file) const;
    void updateMediaFileMetadata(const MediaFile& file, const std::map<std::string, std::string>& metadata);
    void back();

};

#endif // METADATA_CONTROLLER_H
