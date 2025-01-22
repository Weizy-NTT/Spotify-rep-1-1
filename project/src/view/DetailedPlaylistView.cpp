#include <iomanip>
#include "DetailedPlaylistView.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include "MediaFile.hpp"
#include "Playlist.hpp"

using namespace ftxui;

// Display the detailed playlist menu
void DetailedPlaylistView::showMenu() {
    BaseView::showMenu();
    // Create menu using ftxui
    auto menu = Menu(&menu_entries, &selected_option);

    // Create a renderer to display the menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Detailed Playlist Menu ====="),
                   menu->Render(),
                   text("==============================="),
                   text("Use arrow keys or mouse to navigate, press Enter or click to select."),
               }) |
               border;
    });

    // Create a ScreenInteractive for interaction
    auto screen = ScreenInteractive::TerminalOutput();

    // Handle user events for the menu
    auto event_handler = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left && menu->OnEvent(event)) {
                screen.ExitLoopClosure()(); // Exit the loop when the menu is clicked
                return true;
            }          
        }
        if (event == Event::Return) {
            if (menu->OnEvent(event)) {
            screen.ExitLoopClosure()(); // Exit the loop when Enter is pressed
            return true;
            }
        } 
        if (event == Event::Escape || event == Event::Character('q')) {
            screen.ExitLoopClosure()(); // Exit the loop when ESC or 'q' is pressed
            return true;
        }
        return menu->OnEvent(event);

    });

    // Start the interactive screen loop
    screen.Loop(event_handler);
    // std::system("clear");
}

// Get the selected menu option
int DetailedPlaylistView::getSelectedOption() const {
    return selected_option;
}

// Hide the menu and reset the selected option
void DetailedPlaylistView::hideMenu() {
    BaseView::hideMenu();
    selected_option = 0;
    std::system("clear");
}

// Show detailed information about a playlist
void DetailedPlaylistView::showPlaylistDetails(const std::shared_ptr<Playlist>& playlist) {
    using namespace ftxui;

    // 1. Retrieve playlist details
    std::string name = playlist->getName();
    size_t numberOfSongs = playlist->getSongs().size();

    // 2. Create the UI to display playlist details
    auto document = vbox({
        text("Playlist Details") | bold | hcenter,              // Title
        separator(),
        hbox({
            text("Name: ") | bold,                              // Playlist name
            text(name) | color(Color::Yellow)
        }),
        hbox({
            text("Number of Songs: ") | bold,                   // Number of songs
            text(std::to_string(numberOfSongs)) | color(Color::Green)
        }),
        separator(),
        text("Press any key to continue...") | dim | hcenter    // Instructions
    });

    // 3. Adjust the screen to fit the content
    auto screen = Screen::Create(
        Dimension::Full(),         // Full width
        Dimension::Fit(document)   // Fit height
    );
    Render(screen, document);

    // 4. Output the UI to the terminal
    std::cout << screen.ToString() << std::endl;

}

// Display a list of songs in the playlist
void DetailedPlaylistView::showListOfSongs(const std::shared_ptr<Playlist>& playlist) {
    using namespace ftxui;

    // 1. Retrieve the list of songs
    std::vector<std::shared_ptr<MediaFile>> songs = playlist->getSongs();

    // 2. Create elements for each song
    Elements items;
    for (const auto& song : songs) {
        items.push_back(hbox({
            text("[" + song->getID() + "] ") | size(WIDTH, EQUAL, 10),   // Song ID column
            text(song->getName()) | size(WIDTH, GREATER_THAN, 30)       // Song name column
        }));
    }

    // 3. Create the header
    auto header = hbox({
        text("Songs in Playlist: ") | bold,
        text(playlist->getName()) | color(Color::Yellow)
    }) | hcenter;

    // 4. Create the footer
    auto footer = text("Total Songs: " + std::to_string(songs.size())) | hcenter;

    // 5. Combine the header, list, and footer into the document
    auto document = vbox({
        header,
        separator(),
        vbox(std::move(items)) | border, // Display the list
        separator(),
        footer
    });

    // 6. Adjust the screen dimensions
    auto screen = Screen::Create(
        Dimension::Full(),         // Full width
        Dimension::Fit(document)   // Fit height
    );
    Render(screen, document);

    // 7. Output the UI to the terminal
    std::cout << screen.ToString() << std::endl;

}

// Display appropriate status messages based on the status code
void DetailedPlaylistView::displayStatusMessage(DetailedPlaylistStatus& status) {
    switch (status) {
        case DetailedPlaylistStatus::DETAILED_ADD_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in media library or Song ID exists in playlist. Cannot add.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_PLAY_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot play.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_DELETE_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot delete.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_SHOW_STATUS:
            status = DetailedPlaylistStatus::DETAILED_NORMAL;
            std::cout << "Error: Song ID not found in playlist. Cannot show.\n";
            break;
        case DetailedPlaylistStatus::DETAILED_NORMAL:
        default:
            break;
    }
}
