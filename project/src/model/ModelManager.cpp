#include "ModelManager.hpp"

ModelManager::ModelManager() {
    mediaLibrary = std::make_unique<MediaFileLibrary>();
    playlistLibrary = std::make_unique<PlaylistLibrary>();
    playingMedia = std::make_unique<PlayingMedia>();
}

MediaFileLibrary* ModelManager::getMediaLibrary() const {
    return mediaLibrary.get();
}

PlaylistLibrary* ModelManager::getPlaylistLibrary() const {
    return playlistLibrary.get();
}

PlayingMedia* ModelManager::getPlayingMedia() const {
    return playingMedia.get();
}
