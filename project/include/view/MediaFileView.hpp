#ifndef MEDIA_FILE_VIEW_H
#define MEDIA_FILE_VIEW_H

#include "BaseView.hpp"
#include "MediaFile.hpp"
#include <vector>
#include <string>
#include <memory>

// Enum for media file menu options
enum MediaFileMenu {
    PLAY_SONG_FROM_FILES,    // Option to play a song from media files
    SHOW_DETAIL,             // Option to show media file details
    NEXT_PAGE,               // Option to navigate to the next page
    PREV_PAGE,               // Option to navigate to the previous page
    BACK_FROM_MEDIA          // Option to go back to the previous menu
};

// Enum for media file statuses
enum MediaFileStatus {
    MEDIAFILE_NORMAL,             // Normal status
    MEDIAFILE_PLAY_STATUS,        // Status for playing a song
    MEDIAFILE_DETAIL_STATUS,      // Status for showing media file details
    MEDIAFILE_NEXT_PAGE_STATUS,   // Status for navigating to the next page
    MEDIAFILE_PREV_PAGE_STATUS    // Status for navigating to the previous page
};

class MediaFileView : public BaseView {
private:
    // Menu entries for the media file view
    std::vector<std::string> menu_entries = {
        "Play",
        "Show Media File Details",
        "Show Next Page",
        "Show Previous Page",
        "Go Back"
    };
    int selected_option = 0; // Variable to store the user's selected option

public:
    // Override to display the menu
    void showMenu() override;

    // Getter to retrieve the user's selected option
    int getSelectedOption() const;

    // Destructor
    ~MediaFileView() override = default;

    // Display a page of media files
    void showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, size_t currentPage, size_t firstSong, size_t lastSong);

    // Override to hide the menu
    void hideMenu() override;

    // Display a status message based on the current media file status
    void displayStatusMessage(MediaFileStatus& status);
};

#endif // MEDIA_FILE_VIEW_H
