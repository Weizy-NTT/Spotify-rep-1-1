#include "ModelManager.hpp"

MediaFileLibrary ModelManager::getMediaLibrary() const {
    return mediaLibrary;
}

PlaylistLibrary ModelManager::getPlaylistLibrary() const {
    return playlistLibrary;
}

PlayingMedia ModelManager::getPlayingMedia() const {
    return playingMedia;
}

//Device ModelManager::getDevice() const {
//    return device;
//}
