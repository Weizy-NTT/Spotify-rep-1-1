#include "ModelManager.hpp"

// Constructor: Initialize the model components
ModelManager::ModelManager() {
    mediaLibrary = std::make_unique<MediaFileLibrary>();  // Initialize the media library
    playlistLibrary = std::make_unique<PlaylistLibrary>(); // Initialize the playlist library
    playingMedia = std::make_unique<PlayingMedia>(); // Initialize the currently playing media
}

// Retrieve the MediaFileLibrary instance
MediaFileLibrary* ModelManager::getMediaLibrary() const {
    if (mediaLibrary) {
        return mediaLibrary.get(); // Return the pointer to the media library if it exists
    } else {
        return nullptr; // Return nullptr if the media library is not initialized
    }
}

// Retrieve the PlaylistLibrary instance
PlaylistLibrary* ModelManager::getPlaylistLibrary() const {
    if (playlistLibrary) {
        return playlistLibrary.get(); // Return the pointer to the playlist library if it exists
    } else {
        return nullptr; // Return nullptr if the playlist library is not initialized
    }
}

// Retrieve the PlayingMedia instance
PlayingMedia* ModelManager::getPlayingMedia() const {
    if (playingMedia) {
        return playingMedia.get(); // Return the pointer to the currently playing media if it exists
    } else {
        return nullptr; // Return nullptr if the playing media instance is not initialized
    }
}
