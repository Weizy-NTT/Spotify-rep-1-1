#ifndef MAIN_MENU_VIEW_H
#define MAIN_MENU_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>

// Enum for main menu options
enum MainMenu {
    SCAN_OPTIONS,   // Option for scanning files
    ALL_SONGS,      // Option to view all songs
    PLAYLIST,       // Option to view playlists
    NOW_PLAYING,    // Option to view the now playing screen
    EXIT            // Option to exit the application
};

class MainMenuView : public BaseView {
public:
    // Override to display the main menu
    void showMenu() override;

    // Override to hide the main menu
    void hideMenu() override;

    // Getter function to retrieve the selected option
    int getSelectedOption() const;

    // Destructor
    ~MainMenuView() override = default;

private:
    int selected_option = 0;                     // Variable to store the user's selected option
    std::vector<std::string> menu_entries = {    // List of menu entries
        "Scan Options",
        "All Songs",
        "Playlist",
        "Now Playing",
        "Exit"
    };
};

#endif // MAIN_MENU_VIEW_H
