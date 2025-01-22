#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "MediaFileLibrary.hpp"
#include "PlaylistLibrary.hpp"
#include "PlayingMedia.hpp"
#include "Playlist.hpp"
#include <memory>

class ModelManager {
private:
    std::unique_ptr<MediaFileLibrary> mediaLibrary;

    std::unique_ptr<PlaylistLibrary> playlistLibrary;

    std::unique_ptr<PlayingMedia> playingMedia;

public:
    ModelManager();

    MediaFileLibrary* getMediaLibrary() const;

    PlaylistLibrary* getPlaylistLibrary() const;

    PlayingMedia* getPlayingMedia() const;
};

#endif // MODEL_MANAGER_H
