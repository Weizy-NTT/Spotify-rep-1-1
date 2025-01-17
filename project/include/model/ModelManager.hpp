#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "MediaFileLibrary.hpp"
#include "PlaylistLibrary.hpp"
#include "PlayingMedia.hpp"
#include "Device.hpp"
#include "Playlist.hpp"
#include <memory>

class ModelManager {
private:
    std::unique_ptr<MediaFileLibrary> mediaLibrary;
    std::unique_ptr<PlaylistLibrary> playlistLibrary;
    std::unique_ptr<PlayingMedia> playingMedia;
    std::unique_ptr<Device> device;

public:
    MediaFileLibrary* getMediaLibrary() const;
    PlaylistLibrary* getPlaylistLibrary() const;
    PlayingMedia* getPlayingMedia() const;
    Device* getDeviceInfor() const;
    ModelManager();
};

#endif // MODEL_MANAGER_H
