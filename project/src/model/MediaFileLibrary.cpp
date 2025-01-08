#include "MediaFileLibrary.hpp"

std::vector<MediaFile> MediaFileLibrary::getAllMediaFiles() const {
    return mediaFiles;
}

void MediaFileLibrary::addMediaFile(const MediaFile& file) {
    mediaFiles.push_back(file);
}

void MediaFileLibrary::removeMediaFile(const MediaFile& file) {
    for (auto it = mediaFiles.begin();it != mediaFiles.end();it++) {
        if (it->getName() == file.getName()) {
            mediaFiles.erase(it);
            return;
        }
    }
}

MediaFile MediaFileLibrary::getMediaFileByName(const std::string& name) const {
    for (const auto& file : mediaFiles) {
        if (file.getName() == name) {
            return file;
        }
    }
    throw std::runtime_error("Media file not found");
}

void MediaFileLibrary::setAllMediaFiles(const std::vector<MediaFile> files) {
    mediaFiles = files;
}