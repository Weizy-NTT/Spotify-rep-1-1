#include "Metadata.hpp"

std::map<std::string, std::string> Metadata::getMetadata() const {
    return data;
}

void Metadata::setMetadata(const std::map<std::string, std::string>& newData) {
    data = newData;
}

std::string Metadata::getValue(const std::string& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    return "";
}

void Metadata::setValue(const std::string& key, const std::string& value) {
    data[key] = value;
}
