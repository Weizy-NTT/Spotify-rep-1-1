#include "ExceptionLib.hpp"

// Validates if a string contains only alphabetic characters and spaces.
void validateAlphaSring(const std::string& alString) {
    std::regex alStringTemplate(R"([a-zA-Z\s]+)"); // Regex for alphabetic string with spaces.
    if (!std::regex_match(alString, alStringTemplate)) {
        throw InvalidAlphaSringException(); // Throws an exception if validation fails.
    }
}

// Validates if the year is in the correct format and within the valid range.
void validateYear(const std::string& year) {
    std::regex YearTemplate("\\d{4}$"); // Regex for a 4-digit year.
    if (!std::regex_match(year, YearTemplate)) {
        throw InvalidYearException(); // Throws an exception if year format is invalid.
    }
    size_t _year = std::stoi(year);
    if (_year > 2025) { // Ensures the year does not exceed 2025.
        throw InvalidYearException();
    }
}

// Validates if a given value is a positive integer.
void validatePosInteger(const size_t& value) {
    if (value < 0) { // Since size_t is unsigned, this check ensures logical validity.
        throw InvalidInputIntegerException();
    }
}

// Validates menu choice for the Scanf Menu.
void validateScanfMenu(const size_t& value) {
    if (value < 0 || value > 2) { // Valid choices: 0, 1, or 2.
        throw InvalidMenuChoiceException();
    }
}

// Validates menu choice for the Main Menu.
void validateMainMenu(const size_t& value) {
    if (value < 0 || value > 4) { // Valid choices: 0 to 4.
        throw InvalidMenuChoiceException();
    }
}

// Validates menu choice for Media Files Menu.
void validateMediaFilesMenu(const size_t& value) {
    if (value < 0 || value > 4) { // Valid choices: 0 to 4.
        throw InvalidMenuChoiceException();
    }
}

// Validates menu choice for Metadata Menu.
void validateMetadataMenu(const size_t& value) {
    if (value < 0 || value > 1) { // Valid choices: 0 or 1.
        throw InvalidMenuChoiceException();
    }
}

// Validates menu choice for Edit Video Menu.
void validateEditVideoMenu(const size_t& value) {
    if (value < 0 || value > 1) { // Valid choices: 0 or 1.
        throw InvalidMenuChoiceException();
    }
}

// Validates menu choice for Edit Audio Menu.
void validateEditAudioMenu(const size_t& value) {
    if (value < 0 || value > 6) { // Valid choices: 0 to 6.
        throw InvalidMenuChoiceException();
    }
}

// Validates menu choice for Playlists Menu.
void validatePlaylistsMenu(const size_t& value) {
    if (value < 0 || value > 3) { // Valid choices: 0 to 3.
        throw InvalidMenuChoiceException();
    }
}

// Validates menu choice for Detailed Playlist Menu.
void validateDetailedPlaylistMenu(const size_t& value) {
    if (value < 0 || value > 4) { // Valid choices: 0 to 4.
        throw InvalidMenuChoiceException();
    }
}

// Validates menu choice for Playing Media Menu.
void validatePlayingMediaMenu(const size_t& value) {
    if (value < 0 || value > 4) { // Valid choices: 0 to 4.
        throw InvalidMenuChoiceException();
    }
}

// Validates if the volume is within the valid range (0-128).
void validateVolume(const size_t& value) {
    if (value < 0 || value > 128) { // Valid volume range.
        throw InvalidVolumeException();
    }
}

// Validates if an ID contains only digits.
void validateID(const std::string& ID) {
    std::regex idTemplate(R"(\d+)"); // Regex for digits only.
    if (!std::regex_match(ID, idTemplate)) {
        throw InvalidIDException();
    }
}

// Validates if a track value contains only digits.
void validateTrack(const std::string& value) {
    std::regex TrackTemplate(R"(\d+)"); // Regex for digits only.
    if (!std::regex_match(value, TrackTemplate)) {
        throw InvalidTrackException();
    }
}

namespace fs = std::filesystem;

// Validates if a given path exists and is a directory.
void validatePath(const std::string& path) {
    fs::path p(path);
    if (!fs::exists(p) || !fs::is_directory(p)) { // Checks if the path is valid and is a directory.
        throw InvalidPathException();
    }
}

// Checks if a USB device exists.
bool isUSBDevicePresent(const std::string& device) {
    std::ifstream file(device); // Opens the device path as a file.
    return file.good(); // Returns true if the file/device is accessible.
}

// Exception handling wrapper for string inputs.
void Exception_Handler(const std::string& str, std::string& variable, void(*func)(const std::string&)) {
    while (1) {
        try {
            std::cout << str; // Prompt message.
            std::getline(std::cin, variable); // Input from the user.
            func(variable); // Validate the input.
            break; // Exit loop if input is valid.
        } catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl; // Print the error message.
        }
    }
}

// Exception handling wrapper for size_t inputs.
void Exception_Handler(const std::string& str, size_t& variable, void(*func)(const size_t&)) {
    while (1) {
        try {
            std::cout << str; // Prompt message.
            std::cin >> variable; // Input from the user.
            if (std::cin.fail()) { // Check for invalid input.
                throw InvalidInputIntegerException();
            }
            func(variable); // Validate the input.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input.
            break; // Exit loop if input is valid.
        } catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl; // Print the error message.
            std::cin.clear(); // Clear the error state of std::cin.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input.
        }
    }
}
