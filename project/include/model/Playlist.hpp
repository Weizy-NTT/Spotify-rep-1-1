#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "MediaFile.hpp"
#include <memory>
#include <queue>

class Playlist {
private:
    static size_t playlistCount;
    static size_t playlistNextID;
    static std::queue<int> playlistFreeIDs;
    std::string ID;
    std::string name;
    std::vector<std::shared_ptr<MediaFile>> songs;

public:
    Playlist(const std::string& name);
    static void resetIDs();
    std::string getID() const;
    std::string getName() const;
    static size_t getCount();
    const std::vector<std::shared_ptr<MediaFile>>& getSongs() const;
    void addSong(const std::shared_ptr<MediaFile>& song);
    void removeSong(const std::string& ID);
    bool isValidMediaFileIDInPlaylist(const std::string& ID);
    std::shared_ptr<MediaFile> getSongByID(const std::string& ID) const;
    ~Playlist();
};

#endif // PLAYLIST_H
