#include "MediaFile.hpp"

void MediaFile::setName(const std::string& name) {
    this->name = name;
}

void MediaFile::setPath(const std::string& path) {
    this->path = path;
}

std::string MediaFile::getName() const {
    return name;
}

std::string MediaFile::getPath() const {
    return path;
}

MediaType MediaFile::getType() const {
    return type;
}

Metadata MediaFile::getMetadata() const {
    return metadata;
}

void MediaFile::setMetadata(const Metadata& newMetadata) {
    metadata.setMetadata(newMetadata.getMetadata());
}

void MediaFile::setType(MediaType newType) {
    type = newType;
}

