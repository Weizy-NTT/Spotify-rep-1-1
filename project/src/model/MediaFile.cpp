#include "MediaFile.hpp"

size_t MediaFile::mediaFileCount = 0;

MediaFile::MediaFile(const std::string& ID,const std::string& name, const std::string& path, MediaType type, const Metadata& metadata) 
    : ID(ID), name(name), path(path), type(type), metadata(metadata) {mediaFileCount++;}

void MediaFile::setName(const std::string& name) {
    this->name = name;
}

void MediaFile::setPath(const std::string& path) {
    this->path = path;
}

void MediaFile::setID(const std::string& ID) {
    this->ID = ID;
}

std::string MediaFile::getName() const {
    return name;
}

std::string MediaFile::getID() const {
    return ID;
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

MediaFile::~MediaFile() {mediaFileCount--;}

