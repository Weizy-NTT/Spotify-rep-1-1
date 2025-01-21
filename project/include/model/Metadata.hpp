#ifndef METADATA_H
#define METADATA_H

#include <map>
#include <string>

class Metadata {
private:
    std::map<std::string, std::string> data; // Container to store metadata as key-value pairs

public:
    // Retrieve the entire metadata as a map
    std::map<std::string, std::string> getMetadata() const;

    // Set the metadata with a given map of key-value pairs
    void setMetadata(const std::map<std::string, std::string>& data);

    // Get the value associated with a specific key in the metadata
    std::string getValue(const std::string& key) const;

    // Set or update the value for a specific key in the metadata
    void setValue(const std::string& key, const std::string& value);
};

#endif // METADATA_H
