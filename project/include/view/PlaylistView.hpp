#ifndef PLAYLIST_VIEW_H
#define PLAYLIST_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>
#include "Playlist.hpp"

// Enum for playlist statuses
enum PlaylistStatus {
    PLAYLIST_NORMAL,          // Normal status
    PLAYLIST_SELECT_STATUS,   // Status for selecting a playlist
    PLAYLIST_ADD_STATUS,      // Status for adding a playlist
    PLAYLIST_REMOVE_STATUS    // Status for removing a playlist
};

// Enum for playlist menu options
enum PlaylistMenu {
    SELECT_PLAYLIST,          // Option to select a playlist
    ADD_PLAYLIST,             // Option to add a new playlist
    REMOVE_PLAYLIST,          // Option to remove an existing playlist
    BACK_FROM_PLAYLIST        // Option to go back to the previous menu
};

class PlaylistView : public BaseView {
private:
    // Menu entries for the playlist view
    std::vector<std::string> menu_entries = {
        "Select a Playlist",
        "Add a Playlist",
        "Remove a Playlist",
        "Go Back"
    };
    int selected_option = 0; // Variable to store the user's selected option

public:
    // Override to display the menu
    void showMenu() override;

    // Getter to retrieve the user's selected option
    int getSelectedOption() const;

    // Destructor
    ~PlaylistView() override = default;

    // Override to hide the menu
    void hideMenu() override;

    // Display the list of playlists
    void showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists);

    // Display a status message based on the current playlist status
    void displayStatusMessage(PlaylistStatus& status);
};

#endif // PLAYLIST_VIEW_H
