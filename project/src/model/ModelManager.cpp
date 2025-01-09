#include "ModelManager.hpp"

ModelManager::ModelManager() {
    mediaLibrary = std::make_unique<MediaFileLibrary>();
    playlistLibrary = std::make_unique<PlaylistLibrary>();
    playingMedia = std::make_unique<PlayingMedia>();
}

MediaFileLibrary* ModelManager::getMediaLibrary() const {
    if (mediaLibrary) {
        return mediaLibrary.get();
    }
    else {
        return nullptr;
    }
}

PlaylistLibrary* ModelManager::getPlaylistLibrary() const {
    if (mediaLibrary) {
        return playlistLibrary.get();
    }
    else {
        return nullptr;
    }
}

PlayingMedia* ModelManager::getPlayingMedia() const {
    if (mediaLibrary) {
        return playingMedia.get();
    }
    else {
        return nullptr;
    }
}
