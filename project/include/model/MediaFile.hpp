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
    std::string name;
    std::string path;
    MediaType type;
    Metadata metadata;

public:
    MediaFile(const std::string& name = "", const std::string& path = "", MediaType type = AUDIO, const Metadata& metadata = Metadata());
    void setName(const std::string& name);
    void setPath(const std::string& path);
    std::string getName() const;
    std::string getPath() const;
    MediaType getType() const;
    Metadata getMetadata() const;
    void setMetadata(const Metadata& metadata);
    void setType(MediaType type);
};
#endif // MEDIA_FILE_H
