#ifndef DETAILED_PLAYLIST_VIEW_H
#define DETAILED_PLAYLIST_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>
#include <memory>
#include "Playlist.hpp"

// Enum for detailed playlist menu options
enum DetailedPlaylistMenu {
    PLAY_SONG_FROM_PLAYLIST,       // Option to play a song from the playlist
    ADD_SONG,                      // Option to add a song to the playlist
    DELETE_SONG,                   // Option to delete a song from the playlist
    SHOW_DETAIL_SONG,              // Option to show details of a song
    BACK_FROM_DETAIL               // Option to go back to the previous menu
};

// Enum for detailed playlist statuses
enum DetailedPlaylistStatus {
    DETAILED_NORMAL,               // Normal status
    DETAILED_ADD_STATUS,           // Status for adding a song
    DETAILED_PLAY_STATUS,          // Status for playing a song
    DETAILED_DELETE_STATUS,        // Status for deleting a song
    DETAILED_SHOW_STATUS           // Status for showing song details
};

class DetailedPlaylistView : public BaseView {
private:
    // Menu entries for the detailed playlist view
    std::vector<std::string> menu_entries = {
        "Play a song",
        "Add a song to playlist",
        "Delete a song from playlist",
        "Show details of a song",
        "Go Back"
    };
    int selected_option = 0; // Stores the user's selected option

public:
    // Override to display the menu
    void showMenu() override;

    // Override to hide the menu
    void hideMenu() override;

    // Display the details of the playlist
    void showPlaylistDetails(const std::shared_ptr<Playlist>& playlist);

    // Display the list of songs in the playlist
    void showListOfSongs(const std::shared_ptr<Playlist>& playlist);

    // Display a status message based on the current detailed playlist status
    void displayStatusMessage(DetailedPlaylistStatus& status);

    // Return the user's selected option
    int getSelectedOption() const;

    // Destructor
    ~DetailedPlaylistView() override = default;
};

#endif // DETAILED_PLAYLIST_VIEW_H
