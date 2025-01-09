#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "MediaFile.hpp"
#include <memory>


class Playlist {
private:
    std::string ID;
    std::string name;
    std::vector<std::shared_ptr<MediaFile>> songs;

public:
    void setID(const std::string& ID);
    std::string getID() const;
    std::string getName() const;
    const std::vector<std::shared_ptr<MediaFile>>& getSongs() const;
    void addSong(const std::shared_ptr<MediaFile>& song);
    void removeSong(const std::string& ID);
    std::shared_ptr<MediaFile> getSongByID(const std::string& ID) const;
};

#endif // PLAYLIST_H
