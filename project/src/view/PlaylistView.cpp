#include "PlaylistView.hpp"
#include <iostream>
#include <iomanip>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

void PlaylistView::showMenu() {
    BaseView::showMenu(); // Set the menu status to visible

    // Create a menu component with the defined entries
    auto menu = Menu(&menu_entries, &selected_option);

    // Create a renderer to display the menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Playlist Menu ====="),
                   menu->Render(), // Render the menu
                   text("========================="),
                   text("Use arrow keys or mouse to navigate, press Enter or click to select."),
               }) |
               border;
    });

    // Create an interactive screen for displaying the menu
    auto screen = ScreenInteractive::TerminalOutput();

    // Handle user events such as mouse clicks, key presses, etc.
    auto event_handler = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            // Handle mouse click events
            if (event.mouse().button == Mouse::Left && menu->OnEvent(event)) {
                screen.ExitLoopClosure()(); // Exit the loop when a menu item is clicked
                return true;
            }
        }
        if (event == Event::Return) {
            // Handle Enter key event to select a menu item
            if (menu->OnEvent(event)) {
                screen.ExitLoopClosure()();
                return true;
            }
        }
        if (event == Event::Escape || event == Event::Character('q')) {
            // Exit the loop on Escape or 'q' key press
            screen.ExitLoopClosure()();
            return true;
        }
        return menu->OnEvent(event); // Pass other events to the menu
    });

    // Run the interactive screen loop
    screen.Loop(event_handler);
}

int PlaylistView::getSelectedOption() const {
    // Return the index of the currently selected menu option
    return selected_option;
}

void PlaylistView::hideMenu() {
    BaseView::hideMenu(); // Set the menu status to hidden
    selected_option = 0;  // Reset the selected option index
    std::system("clear"); // Clear the terminal screen
}

void PlaylistView::showPlaylistList(const std::vector<std::shared_ptr<Playlist>>& playlists) {
    using namespace ftxui;

    // 1. Create a list of playlists
    Elements items;
    for (const auto& playlist : playlists) {
        items.push_back(hbox({
            text("[" + playlist->getID() + "] ") | size(WIDTH, EQUAL, 10), // Column for Playlist ID
            text(playlist->getName()) | size(WIDTH, GREATER_THAN, 30)     // Column for Playlist Name
        }));
    }

    // 2. Create a header
    auto header = text("============= Playlist List =============") | bold | hcenter;

    // 3. Create a footer
    auto footer = text("Total Playlists: " + std::to_string(playlists.size())) | hcenter;

    // 4. Combine all elements into a single layout
    auto document = vbox({
        header,
        separator(),
        vbox(std::move(items)) | border, // Display the list of playlists
        separator(),
        footer
    });

    // 5. Adjust the screen dimensions to fit the content
    auto screen = Screen::Create(
        Dimension::Full(),         // Use full width
        Dimension::Fit(document)   // Adjust height to fit the content
    );
    Render(screen, document);

    // 6. Display the content in the terminal
    std::cout << screen.ToString() << std::endl;
}

void PlaylistView::displayStatusMessage(PlaylistStatus& status) {
    // Display appropriate status messages based on the current status
    switch (status) {
        case PlaylistStatus::PLAYLIST_SELECT_STATUS:
            std::cout << "Error: The playlist ID was not found in the library.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset status to normal after displaying the error
            break;
        case PlaylistStatus::PLAYLIST_ADD_STATUS:
            std::cout << "Error: Could not add playlist. Please try again.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset status to normal after displaying the error
            break;
        case PlaylistStatus::PLAYLIST_REMOVE_STATUS:
            std::cout << "Error: The playlist ID was not found in the library. Could not remove.\n";
            status = PlaylistStatus::PLAYLIST_NORMAL;  // Reset status to normal after displaying the error
            break;
        case PlaylistStatus::PLAYLIST_NORMAL:
        default:
            // No action needed for normal status
            break;
    }
}
