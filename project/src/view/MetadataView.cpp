#include "MetadataView.hpp"
#include <iostream>
#include <iomanip>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // For text, vbox, border elements

using namespace ftxui;

void MetadataView::showMenu() {
    BaseView::showMenu();

    // Create a menu with predefined entries
    auto menu = Menu(&menu_entries, &selected_option);

    // Create a renderer to display the menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Metadata Menu ====="),
                   menu->Render(),
                   text("========================="),
                   text("Use arrow keys or mouse to navigate, press Enter or click to select."),
               }) |
               border;
    });

    // Create a ScreenInteractive object for handling user interactions
    auto screen = ScreenInteractive::TerminalOutput();

    // Handle events
    auto event_handler = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left && menu->OnEvent(event)) {
                screen.ExitLoopClosure()(); // Exit loop when clicking on a menu item
                return true;
            }
        }

        // Handle Enter key press (similar to clicking)
        if (event == Event::Return) {
            if (menu->OnEvent(event)) {
                screen.ExitLoopClosure()();
                return true;
            }
        }

        // Exit loop when pressing ESC or 'q'
        if (event == Event::Escape || event == Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        return menu->OnEvent(event);
    });

    // Run the UI loop
    screen.Loop(event_handler);
    std::system("clear");
}

void MetadataView::hideMenu() {
    BaseView::hideMenu();
    selected_option = 0;
    selected_option_audio = 0;
    selected_option_video = 0;
    std::system("clear");
}

// Get the selected menu option
int MetadataView::getSelectedOption() const {
    return selected_option;
}

void MetadataView::showFileMetadata(const std::shared_ptr<MediaFile>& file) {
    using namespace ftxui;

    auto metadata = file->getMetadata();

    // 1. Create the header for the metadata display
    auto header = hbox({
        text("METADATA OF: ") | bold,
        text(file->getName()) | color(Color::Yellow)
    }) | hcenter;

    // 2. Create the content rows for metadata attributes
    Elements rows;
    for (const auto& entry : metadata.getMetadata()) {
        rows.push_back(hbox({
            text(entry.first + ":") | size(WIDTH, EQUAL, 15),   // Metadata attribute name
            text(entry.second) | size(WIDTH, GREATER_THAN, 25) // Metadata attribute value
        }));
    }

    auto content = vbox(std::move(rows)) | border;

    // 3. Create the complete interface
    auto document = vbox({
        header,
        separator(),
        content,
        separator(),
        text("Metadata Editing") | dim | hcenter
    });

    // 4. Adjust the screen size based on the content
    auto screen = Screen::Create(
        Dimension::Full(),         // Full width
        Dimension::Fit(document)   // Fit height to content
    );
    Render(screen, document);

    // 5. Display the interface in the terminal
    std::cout << screen.ToString() << std::endl;
}

void MetadataView::menuEditAudio() {
    BaseView::showMenu();

    // Define menu options for Audio Edit
    std::vector<std::string> audio_edit_entries = {
        "Edit Title",
        "Edit Artist",
        "Edit Album",
        "Edit Year",
        "Edit Track",
        "Edit Genre",
        "Back"
    };

    // Create the menu for Audio Edit
    auto menu_audio = Menu(&audio_edit_entries, &selected_option_audio);

    // Create a renderer to display the Audio Edit menu
    auto renderer_audio = Renderer(menu_audio, [&] {
        return vbox({
            text("===== Audio Edit Menu =====") | bold | center,
            menu_audio->Render(),
            text("==========================="),
            text("Use arrow keys or mouse to navigate, press Enter or click to select."),
        }) |
        border;
    });

    // Create a ScreenInteractive object for handling user events
    auto screen = ScreenInteractive::TerminalOutput();

    // Handle user events for Audio Edit
    auto event_handler = CatchEvent(renderer_audio, [&](Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left && menu_audio->OnEvent(event)) {
                std::cout << "Audio Option " << selected_option_audio << " selected via mouse!" << std::endl;
                screen.ExitLoopClosure()();  // Exit loop when a menu item is clicked
                return true;
            }
        }

        if (event == Event::Return) { // Handle Enter key
            if (menu_audio->OnEvent(event)) {
                screen.ExitLoopClosure()();
                return true;
            }
        }

        if (event == Event::Escape || event == Event::Character('q')) { // Handle ESC or 'q' key
            std::cout << "Exiting Audio Edit menu..." << std::endl;
            screen.ExitLoopClosure()();
            return true;
        }

        return menu_audio->OnEvent(event); // Handle other events
    });

    // Run the interactive UI loop
    screen.Loop(event_handler);
}

void MetadataView::menuEditVideo() {
    BaseView::showMenu();

    // Define menu options for Video Edit
    std::vector<std::string> video_edit_entries = {
        "Edit Title",
        "Back"
    };

    // Create the menu for Video Edit
    auto menu_video = Menu(&video_edit_entries, &selected_option_video);

    // Create a renderer to display the Video Edit menu
    auto renderer_video = Renderer(menu_video, [&] {
        return vbox({
            text("===== Video Edit Menu =====") | bold | hcenter,
            menu_video->Render(),
            text("==========================="),
            text("Use arrow keys or mouse to navigate, press Enter or click to select."),
        }) |
        border;
    });

    // Create a ScreenInteractive object for handling user events
    auto screen = ScreenInteractive::TerminalOutput();

    // Handle user events for Video Edit
    auto event_handler = CatchEvent(renderer_video, [&](Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left && menu_video->OnEvent(event)) {
                std::cout << "Video Option " << selected_option_video << " selected via mouse!" << std::endl;
                screen.ExitLoopClosure()();  // Exit loop when a menu item is clicked
                return true;
            }
        }

        if (event == Event::Return) { // Handle Enter key
            if (menu_video->OnEvent(event)) {
                screen.ExitLoopClosure()();
                return true;
            }
        }

        if (event == Event::Escape || event == Event::Character('q')) { // Handle ESC or 'q' key
            std::cout << "Exiting Video Edit menu..." << std::endl;
            screen.ExitLoopClosure()();
            return true;
        }

        return menu_video->OnEvent(event); // Handle other events
    });

    // Run the interactive UI loop
    screen.Loop(event_handler);
}

// Return the selected option for the Audio Edit menu
int MetadataView::getAuditoOption() const {
    return selected_option_audio;
}

// Return the selected option for the Video Edit menu
int MetadataView::getVideoOption() const {
    return selected_option_video;
}






