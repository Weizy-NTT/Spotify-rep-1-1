// #include "ViewManager.hpp"
// #include "ModelManager.hpp"
// #include "ControllerManager.hpp"
// #include <iostream>
// #include "ExceptionLib.hpp"

// int main() {

//     while(1) {
//         ControllerManager::getInstance(new ViewManager,new ModelManager)->getViewManager()->showCurrentView();
//         size_t mainChoice;
//         Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);

//         switch (mainChoice)
//         {
//         case MainMenu::SCAN_OPTIONS: {
//             ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<ScanfOptionView>());
//             size_t scanfChoice;
//             std::string path;
//             Exception_Handler("Enter your choice: ",scanfChoice,validatePosInteger);
//             switch (scanfChoice) {
//                 case ScanfMenu::SCANF_DIRECTORY:
//                     Exception_Handler("Enter directory path: ",path,validateFullName);
//                     ControllerManager::getInstance()->getModelManager()->getMediaLibrary().setAllMediaFiles(ControllerManager::getInstance()->getScanfOptionController().scanDirectory(path));
//                     break;
//                 case ScanfMenu::SCANF_USB:
//                     break;
//                 case ScanfMenu::BACK_FROM_SCAN:
//                     break;
//                 default:
//                     std::cout << "Your choice is not valid\n";
//                     break;
//             }
//             break;
//         }
//         case MainMenu::ALL_SONGS:
//             ControllerManager::getInstance()->getViewManager()->getMediaFileView()->showMediaFilesPage(ControllerManager::getInstance()->getModelManager()->getMediaLibrary().getAllMediaFiles(),1,0,1);
//             ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<MediaFileView>());
//             break;
//         case MainMenu::PLAYLIST:
//             ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<PlaylistView>());
//             break;
//         case MainMenu::EXIT:
//             std::cout << "Exiting the program....\n";
//             return 0;
//         default:
//             std::cout << "Your choice is not valid\n";
//             break;
//         }
//         ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<MainMenuView>());
//     }
//     return 0;
// }

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

struct OriginalMetadata {
    std::string filePath;
    std::string title;
    std::string artist;
    std::string album;
    unsigned int year;
    unsigned int track;
    std::string genre;
    unsigned int duration; // length of the song
};

void printMetadata(TagLib::Tag* tag, TagLib::AudioProperties* audioProperties) {
    std::cout << "General Information:" << std::endl;
    std::cout << "Title    : " << tag->title().toCString(true) << std::endl;
    std::cout << "Artist   : " << tag->artist().toCString(true) << std::endl;
    std::cout << "Album    : " << tag->album().toCString(true) << std::endl;
    std::cout << "Year     : " << tag->year() << std::endl;
    std::cout << "Duration : " << audioProperties->length() << " seconds" << std::endl;

    std::cout << "\nAudio Information:" << std::endl;
    std::cout << "Channels : " << audioProperties->channels() << std::endl;
    std::cout << "Sample Rate : " << audioProperties->sampleRate() << " Hz" << std::endl;
    std::cout << "Bitrate : " << audioProperties->bitrate() << " kbps" << std::endl;
}

void restoreMetadata(TagLib::Tag* tag, const OriginalMetadata& originalMetadata) {
    tag->setTitle(TagLib::String(originalMetadata.title));
    tag->setArtist(TagLib::String(originalMetadata.artist));
    tag->setAlbum(TagLib::String(originalMetadata.album));
    tag->setYear(originalMetadata.year);
    tag->setTrack(originalMetadata.track);
    tag->setGenre(TagLib::String(originalMetadata.genre));
}

void processFile(const std::string& filepath) {
    TagLib::FileRef f(filepath.c_str());

    if (!f.isNull() && f.tag() && f.audioProperties()) {
        TagLib::Tag* tag = f.tag();
        TagLib::AudioProperties* audioProperties = f.audioProperties();

        OriginalMetadata originalMetadata = {
            filepath,
            tag->title().toCString(true),
            tag->artist().toCString(true),
            tag->album().toCString(true),
            tag->year(),
            tag->track(),
            tag->genre().toCString(true),
            static_cast<unsigned int>(audioProperties->length())
        };

        std::cout << "\nProcessing file: " << filepath << std::endl;
        printMetadata(tag, audioProperties);

        int choice;
        do {
            std::cout << "\nChoose an option to edit metadata (0 to exit, 7 to restore original values):" << std::endl;
            std::cout << "1. Edit Title" << std::endl;
            std::cout << "2. Edit Artist" << std::endl;
            std::cout << "3. Edit Album" << std::endl;
            std::cout << "4. Edit Genre" << std::endl;
            std::cout << "5. Edit Year" << std::endl;
            std::cout << "6. Edit Track" << std::endl;
            std::cout << "7. Restore Original Values" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();

            std::string newValue;
            unsigned int newNumber;
            switch (choice) {
                case 1:
                    std::cout << "Enter new title: ";
                    std::getline(std::cin, newValue);
                    tag->setTitle(TagLib::String(newValue));
                    break;
                case 2:
                    std::cout << "Enter new artist: ";
                    std::getline(std::cin, newValue);
                    tag->setArtist(TagLib::String(newValue));
                    break;
                case 3:
                    std::cout << "Enter new album: ";
                    std::getline(std::cin, newValue);
                    tag->setAlbum(TagLib::String(newValue));
                    break;
                case 4:
                    std::cout << "Enter new genre: ";
                    std::getline(std::cin, newValue);
                    tag->setGenre(TagLib::String(newValue));
                    break;
                case 5:
                    std::cout << "Enter new year: ";
                    std::cin >> newNumber;
                    tag->setYear(newNumber);
                    std::cin.ignore();
                    break;
                case 6:
                    std::cout << "Enter new track number: ";
                    std::cin >> newNumber;
                    tag->setTrack(newNumber);
                    std::cin.ignore();
                    break;
                case 7:
                    std::cout << "Restoring original values..." << std::endl;
                    restoreMetadata(tag, originalMetadata);
                    break;
                case 0:
                    std::cout << "Exiting editing..." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice, please try again." << std::endl;
            }

            if (choice != 0) {
                printMetadata(tag, audioProperties);
            }
        } while (choice != 0);

        if (f.save()) {
            std::cout << "\nMetadata updated successfully for " << filepath << std::endl;
        } else {
            std::cerr << "Error: Could not save changes to the file." << std::endl;
        }
    } else {
        std::cerr << "Error: Could not open file or retrieve metadata for " << filepath << std::endl;
    }
}

std::vector<OriginalMetadata> scanDirectory(const std::string& folderPath) {
    std::vector<OriginalMetadata> songList;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            TagLib::FileRef f(entry.path().c_str());

            if (!f.isNull() && f.tag() && f.audioProperties()) {
                TagLib::Tag* tag = f.tag();
                TagLib::AudioProperties* audioProperties = f.audioProperties();

                OriginalMetadata metadata = {
                    entry.path().string(),
                    tag->title().toCString(true),
                    tag->artist().toCString(true),
                    tag->album().toCString(true),
                    tag->year(),
                    tag->track(),
                    tag->genre().toCString(true),
                    static_cast<unsigned int>(audioProperties->length())
                };

                songList.push_back(metadata);
            } else {
                std::cerr << "Error: Could not retrieve metadata for " << entry.path() << std::endl;
            }
        }
    }

    return songList;
}

void displaySongs(const std::vector<OriginalMetadata>& songList) {
    std::cout << "\nList of Songs:\n";
    for (size_t i = 0; i < songList.size(); ++i) {
        const auto& song = songList[i];
        std::cout << i + 1 << ". " << song.title << " - " << song.artist 
                  << " (" << song.album << ", " << song.year << ")" 
                  << " [Duration: " << song.duration << "s]" << std::endl;
        TagLib::FileRef f(song.filePath.c_str());
        if (!f.isNull() && f.tag() && f.audioProperties()) {
            printMetadata(f.tag(), f.audioProperties());
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string folderPath = "./resources/playlists";

    std::vector<OriginalMetadata> songList = scanDirectory(folderPath);

    if (!songList.empty()) {
        displaySongs(songList);

        int choice;
        do {
            std::cout << "\nEnter the number of the song to edit metadata (0 to exit): ";
            std::cin >> choice;
            std::cin.ignore();

            if (choice > 0 && choice <= static_cast<int>(songList.size())) {
                processFile(songList[choice - 1].filePath);
            } else if (choice != 0) {
                std::cout << "Invalid choice, please try again." << std::endl;
            }
        } while (choice != 0);
    } else {
        std::cout << "No songs found in the specified folder." << std::endl;
    }

    return 0;
}
