#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "MediaFileLibrary.hpp"
#include "PlaylistLibrary.hpp"
#include "PlayingMedia.hpp"
#include "Device.hpp"

class ModelManager {
private:
    MediaFileLibrary mediaLibrary;
    PlaylistLibrary playlistLibrary;
    PlayingMedia playingMedia;
    //Device device;

public:
    MediaFileLibrary getMediaLibrary() const;
    PlaylistLibrary getPlaylistLibrary() const;
    PlayingMedia getPlayingMedia() const;
    //Device getDevice() const;
};

#endif // MODEL_MANAGER_H
