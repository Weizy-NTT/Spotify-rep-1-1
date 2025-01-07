#ifndef METADATA_CONTROLLER_H
#define METADATA_CONTROLLER_H

#include <map>
#include "MediaFile.hpp"

class MetadataController {
public:
    std::map<std::string, std::string> getMediaFileMetadata(const MediaFile& file) const;
    void updateMediaFileMetadata(const MediaFile& file, const std::map<std::string, std::string>& metadata);
};

#endif // METADATA_CONTROLLER_H
