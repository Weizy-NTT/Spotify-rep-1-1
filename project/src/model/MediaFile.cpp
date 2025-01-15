#include "MediaFile.hpp"

size_t MediaFile::mediaFileNextID = 1;
std::queue<int> MediaFile::mediaFileFreeIDs;

MediaFile::MediaFile(const std::string& name, const std::string& path, MediaType type, const Metadata& metadata) 
    :name(name), path(path), type(type), metadata(metadata) 
    {
    if (!mediaFileFreeIDs.empty()) {
        ID = std::to_string(mediaFileFreeIDs.front());
        mediaFileFreeIDs.pop();
    } else {
        ID = std::to_string(mediaFileNextID++);
    }
    }

void MediaFile::setName(const std::string& name) {
    this->name = name;
}

void MediaFile::setPath(const std::string& path) {
    this->path = path;
}

void MediaFile::setDuration(const size_t& duration) {
    this->duration = duration;
}

std::string MediaFile::getName() const {
    return name;
}

std::string MediaFile::getID() const {
    return ID;
}

size_t MediaFile::getDuration() const {
    return duration;
}

std::string MediaFile::getPath() const {
    return path;
}

MediaType MediaFile::getType() const {
    return type;
}

Metadata& MediaFile::getMetadata(){
    return metadata;
}

void MediaFile::setMetadata(const Metadata& newMetadata) {
    metadata.setMetadata(newMetadata.getMetadata());
}

void MediaFile::setType(MediaType newType) {
    type = newType;
}

MediaFile::~MediaFile() {
    mediaFileFreeIDs.push(std::stoi(ID));
}

