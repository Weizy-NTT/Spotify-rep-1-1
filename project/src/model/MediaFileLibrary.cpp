#include "MediaFileLibrary.hpp"
#include <algorithm> // std::find_if, std::remove_if

const std::vector<std::shared_ptr<MediaFile>>& MediaFileLibrary::getAllMediaFiles() const {
    return mediaFiles;
}

void MediaFileLibrary::addMediaFile(const std::shared_ptr<MediaFile>& file) {
    mediaFiles.push_back(file);
}

void MediaFileLibrary::removeMediaFile(const std::string& ID) {
    for (auto it = mediaFiles.begin();it != mediaFiles.end();it++) {
        if (it->get()->getID() == ID) {
            mediaFiles.erase(it);
            return;
        }
    }
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
