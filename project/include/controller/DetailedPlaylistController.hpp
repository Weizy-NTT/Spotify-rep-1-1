#ifndef DETAILED_PLAYLIST_CONTROLLER_H
#define DETAILED_PLAYLIST_CONTROLLER_H

#include "Playlist.hpp"
#include "MediaFile.hpp"

class DetailedPlaylistController {
public:
    Playlist getPlaylistDetails(const std::string& playlistName) const;
    void addSongToPlaylist(const std::string& playlistName, const MediaFile& song);
    void removeSongFromPlaylist(const std::string& playlistName, const MediaFile& song);
};

#endif // DETAILED_PLAYLIST_CONTROLLER_H
