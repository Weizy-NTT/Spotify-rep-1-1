#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "MediaFile.hpp"

class Playlist {
private:
    std::string name;
    std::vector<MediaFile> songs;

public:
    std::string getName() const;
    std::vector<MediaFile> getSongs() const;
    void addSong(const MediaFile& song);
    void removeSong(const MediaFile& song);
    MediaFile getSongByName(const std::string& nameSong);
};

#endif // PLAYLIST_H
