#ifndef EXCEPTION_H
#define EXCEPTION_H

#include<bits/stdc++.h>

class InvalidAlphaSringException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid input. Only alpha characters are allowed.";
    }
};

class InvalidYearException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Year must have 4 numeric characters.";
    }
};

class InvalidInputIntegerException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid input. Input must be an positive integer value";
    }
};

class InvalidMenuChoiceException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid choice. Please enter a valid option from the menu.";
    }
};

class InvalidIDException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid ID. ID must contain only digits.";
    }
};

class InvalidTrackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid track number. Track number must contain only digits.";
    }
};

class InvalidPathException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid path. The path does not exist or is not a valid directory.";
    }
};

class InvalidVolumeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid volume. The volume must be between 0 and 128.";
    }
};

void validateVolume(const size_t& value);
void validateScanfMenu(const size_t& value);
void validateMainMenu(const size_t& value);
void validateMediaFilesMenu(const size_t& value);
void validateMetadataMenu(const size_t& value);
void validateEditVideoMenu(const size_t& value);
void validateEditAudioMenu(const size_t& value);
void validatePlaylistsMenu(const size_t& value);
void validateDetailedPlaylistMenu(const size_t& value);
void validatePlayingMediaMenu(const size_t& value);

void validateID(const std::string& ID);
void validateTrack(const std::string& value);
void validatePath(const std::string& path);
bool isUSBDevicePresent(const std::string& device);

void validateAlphaSring(const std::string& alString);
void validateYear(const std::string& year);
void validatePosInteger(const size_t& value);
void Exception_Handler(const std::string& str,std::string& variable, void(*func)(const std::string&));
void Exception_Handler(const std::string& str,size_t& variable, void(*func)(const size_t&));
#endif // EXCEPTION_H
