#ifndef MEDIA_FILE_H
#define MEDIA_FILE_H

#include <string>
#include <map>
#include <vector>
#include "Metadata.hpp"

enum MediaType {
    AUDIO,
    VIDEO
};

class MediaFile {
private:
    static size_t mediaFileCount;
    std::string ID;
    std::string name;
    std::string path;
    MediaType type;
    Metadata metadata;

public:
    MediaFile(const std::string& ID = "",const std::string& name = "", const std::string& path = "", MediaType type = AUDIO, const Metadata& metadata = Metadata());
    void setName(const std::string& name);
    void setID(const std::string& ID);
    void setPath(const std::string& path);
    std::string getName() const;
    std::string getID() const;
    std::string getPath() const;
    MediaType getType() const;
    Metadata& getMetadata();
    void setMetadata(const Metadata& metadata);
    void setType(MediaType type);
    ~MediaFile();
};
#endif // MEDIA_FILE_H
