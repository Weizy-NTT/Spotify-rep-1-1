#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include "ScanfOptionController.hpp"
#include "PlaylistController.hpp"
#include "MediaFileController.hpp"
#include "PlayingMediaController.hpp"
#include "DetailedPlaylistController.hpp"
#include "MetadataController.hpp"

class ControllerManager {
private:
    ScanfOptionController fileController;
    PlaylistController playlistController;
    MediaFileController mediaFileController;
    PlayingMediaController playingMediaController;
    DetailedPlaylistController detailedPlaylistController;
    MetadataController metadataController;

public:
    ScanfOptionController getFileController() const;
    PlaylistController getPlaylistController() const;
    MediaFileController getMediaFileController() const;
    PlayingMediaController getPlayingMediaController() const;
    DetailedPlaylistController getDetailedPlaylistController() const;
    MetadataController getMetadataController() const;
};

#endif // CONTROLLER_MANAGER_H
