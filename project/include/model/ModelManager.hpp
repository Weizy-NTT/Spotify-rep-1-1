#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "MediaFileLibrary.hpp"
#include "PlaylistLibrary.hpp"
#include "PlayingMedia.hpp"
#include "Playlist.hpp"
#include <memory>

class ModelManager {
private:
    // Pointer to the media file library, managing all media files
    std::unique_ptr<MediaFileLibrary> mediaLibrary;

    // Pointer to the playlist library, managing all playlists
    std::unique_ptr<PlaylistLibrary> playlistLibrary;

    // Pointer to the currently playing media instance
    std::unique_ptr<PlayingMedia> playingMedia;

public:
    // Constructor to initialize ModelManager
    ModelManager();

    // Get the media file library instance
    MediaFileLibrary* getMediaLibrary() const;

    // Get the playlist library instance
    PlaylistLibrary* getPlaylistLibrary() const;

    // Get the currently playing media instance
    PlayingMedia* getPlayingMedia() const;
};

#endif // MODEL_MANAGER_H
