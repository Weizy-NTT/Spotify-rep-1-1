#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "MediaFile.hpp"
#include <memory>
#include <queue>

class Playlist {
private:
    static size_t playlistNextID;                
    std::string ID;                                
    std::string name;                            
    std::vector<std::shared_ptr<MediaFile>> songs; 

public:
    Playlist(const std::string& name);

    std::string getID() const;

    std::string getName() const;
    void setID(const std::string& ID);
    const std::vector<std::shared_ptr<MediaFile>>& getSongs() const;

    void addSong(const std::shared_ptr<MediaFile>& song);

    void removeSong(const std::string& ID);

    bool isValidMediaFileIDInPlaylist(const std::string& ID);

    std::shared_ptr<MediaFile> getSongByID(const std::string& ID) const;

    ~Playlist();
};

#endif // PLAYLIST_H
