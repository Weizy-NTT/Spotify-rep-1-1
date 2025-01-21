#ifndef MEDIA_FILE_H
#define MEDIA_FILE_H

#include <string>
#include <map>
#include <vector>
#include "Metadata.hpp"
#include <queue>

// Enumeration for the type of media files
enum MediaType {
    AUDIO,   // Represents audio files
    VIDEO,   // Represents video files
    UNKNOWN  // Represents an unknown media type
};

class MediaFile {
private:
    static size_t mediaFileNextID;           // Static variable to track the next unique ID for media files
    static std::queue<int> mediaFileFreeIDs; // Queue to manage freed IDs for reuse
    std::string ID;                          // Unique identifier for the media file
    std::string name;                        // Name of the media file
    std::string path;                        // File path of the media file
    size_t duration;                         // Duration of the media file in seconds
    MediaType type;                          // Type of the media (e.g., AUDIO, VIDEO)
    Metadata metadata;                       // Metadata associated with the media file

public:
    // Constructor to initialize a media file with optional parameters
    MediaFile(const std::string& name = "", const std::string& path = "", MediaType type = AUDIO, const Metadata& metadata = Metadata());

    // Set the name of the media file
    void setName(const std::string& name);

    // Set the file path of the media file
    void setPath(const std::string& path);

    // Set the duration of the media file
    void setDuration(const size_t& duration);

    // Get the name of the media file
    std::string getName() const;

    // Get the unique identifier of the media file
    std::string getID() const;

    // Get the duration of the media file
    size_t getDuration() const;

    // Get the file path of the media file
    std::string getPath() const;

    // Get the type of the media file
    MediaType getType() const;

    // Get a reference to the metadata of the media file
    Metadata& getMetadata();

    // Set the metadata of the media file
    void setMetadata(const Metadata& metadata);

    // Set the type of the media file
    void setType(MediaType type);

    // Destructor for the MediaFile class
    ~MediaFile();
};

#endif // MEDIA_FILE_H
