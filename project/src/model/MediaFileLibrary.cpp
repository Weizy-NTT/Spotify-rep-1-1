#include "MediaFileLibrary.hpp"
#include <algorithm>

const std::vector<std::shared_ptr<MediaFile>>& MediaFileLibrary::getAllMediaFiles() const {
    return mediaFiles;
}

void MediaFileLibrary::addMediaFile(const std::shared_ptr<MediaFile>& file) {
    if(!isValidMediaFileIDInLibrary(file->getID())){
        mediaFiles.push_back(file);
    }
}

void MediaFileLibrary::removeMediaFile(const std::string& ID) {
    for (auto it = mediaFiles.begin();it != mediaFiles.end();it++) {
        if (it->get()->getID() == ID) {
            mediaFiles.erase(it);
            return;
        }
    }
}

bool MediaFileLibrary::isValidMediaFileIDInLibrary(const std::string& ID) {
    for (const auto& mediaFile : mediaFiles) {
        if (mediaFile->getID() == ID) {
            return true;
        }
    }
    return false;
}

bool MediaFileLibrary::isValidMediaFileNameInLibrary(const std::string& fileName) {
    for (const auto& mediaFile : mediaFiles) {
        if (mediaFile->getName() == fileName) {
            return true;
        }
    }
    return false;
}

void MediaFileLibrary::setAllMediaFiles(const std::vector<std::shared_ptr<MediaFile>>& files) {
    mediaFiles = files;
}

std::shared_ptr<MediaFile> MediaFileLibrary::getMediaFileByID(const std::string& ID) const {
    for (const auto& mediaFile : mediaFiles) {
        if (mediaFile->getID() == ID) {
            return mediaFile;
        }
    }
    return nullptr;
}

std::shared_ptr<MediaFile> MediaFileLibrary::getMediaFileByName(const std::string& fileName) const {
    for (const auto& mediaFile : mediaFiles) {
        if (mediaFile->getName() == fileName) {
            return mediaFile;
        }
    }
    return nullptr;
}
