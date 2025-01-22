#include "MediaFileView.hpp"
#include <iostream>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>

using namespace ftxui;

void MediaFileView::showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, size_t currentPage, size_t firstSong, size_t lastSong) {
    using namespace ftxui;

    // 1. Create the list of media files
    Elements items;
    for (size_t i = firstSong; i <= lastSong && i < files.size(); ++i) {
        items.push_back(hbox({
            text("[" + files[i]->getID() + "] ") | size(WIDTH, EQUAL, 10), // ID column
            text(files[i]->getName()) | size(WIDTH, GREATER_THAN, 30)      // Name column
        }));
    }

    // 2. Create footer with current page information
    std::string footer = "Page " + std::to_string(currentPage);

    // 3. Build the interface
    auto document = vbox({
        text("Media Files") | bold | hcenter,   // Title
        separator(),
        vbox(std::move(items)) | border,       // Auto-fit list
        separator(),
        text(footer) | hcenter                 // Footer
    });

    // 4. Adjust screen size based on content
    auto screen = Screen::Create(
        Dimension::Full(),         // Full-width
        Dimension::Fit(document)   // Fit height to content
    );
    Render(screen, document);

    // 5. Output the interface to the terminal
    std::cout << screen.ToString() << std::endl;
}

void MediaFileView::showMenu() {
    BaseView::showMenu();
    // Create the menu with predefined entries
    auto menu = Menu(&menu_entries, &selected_option);

    // Create a renderer to display the menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("==== Media Player Menu ===="),
                   menu->Render(),
                   text("==========================="),
                   text("Use arrow keys or mouse to navigate, press Enter or click to select."),
               }) |
               border;
    });

    // Create a ScreenInteractive object for user interaction
    auto screen = ScreenInteractive::TerminalOutput();

    // Handle events
    auto event_handler = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left && menu->OnEvent(event)) {
                screen.ExitLoopClosure()(); // Exit the loop when clicking on a menu item
                return true;
            }
        }
        if (event == Event::Return) {
            if (menu->OnEvent(event)) {
                screen.ExitLoopClosure()(); // Exit the loop when pressing Enter
                return true;
            }
        } 
        if (event == Event::Escape || event == Event::Character('q')) {
            screen.ExitLoopClosure()(); // Exit the loop when pressing ESC or 'q'
            return true;
        }
        return menu->OnEvent(event);
    });

    // Run the UI loop
    screen.Loop(event_handler);
    std::system("clear");
}

// Get the selected menu option
int MediaFileView::getSelectedOption() const {
    return selected_option;
}

// Hide the menu and reset the selected option
void MediaFileView::hideMenu() {
    BaseView::hideMenu();
    selected_option = 0;
    std::system("clear");
}

void MediaFileView::displayStatusMessage(MediaFileStatus& status) {
    switch (status) {
        case MediaFileStatus::MEDIAFILE_PLAY_STATUS:
            std::cout << "Song ID not found in media library. Cannot play.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset the status
            break;
        case MediaFileStatus::MEDIAFILE_DETAIL_STATUS:
            std::cout << "Song ID not found in media library. Cannot show details.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset the status
            break;
        case MediaFileStatus::MEDIAFILE_NEXT_PAGE_STATUS:
            std::cout << "This is the last page. Cannot go next.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset the status
            break;
        case MediaFileStatus::MEDIAFILE_PREV_PAGE_STATUS:
            std::cout << "This is the first page. Cannot go back.\n";
            status = MediaFileStatus::MEDIAFILE_NORMAL;  // Reset the status
            break;
        case MediaFileStatus::MEDIAFILE_NORMAL:
        default:
            // No action needed for normal status
            break;
    }
}
