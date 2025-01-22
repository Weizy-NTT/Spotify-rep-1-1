#include "ScanfOptionView.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // To use text, vbox, border
#include <iostream>
using namespace ftxui;

void ScanfOptionView::showMenu() {
    BaseView::showMenu(); // Set the view status to visible
    // Create the menu
    auto menu = Menu(&menu_entries, &selected_option);

    // Create a renderer to display the menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Scanf Option Menu ====="),
                   menu->Render(), // Render the menu items
                   text("============================="),
                   text("Use arrow keys or mouse to navigate, press Enter or click to select."),
               }) |
               border;
    });

    // Create a ScreenInteractive object to handle events
    auto screen = ScreenInteractive::TerminalOutput();

    // Handle events
    auto event_handler = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            // Handle mouse events
            if (event.mouse().button == Mouse::Left && menu->OnEvent(event)) {
                screen.ExitLoopClosure()(); // Exit the loop when a menu item is clicked
                return true;
            }
        }
        if (event == Event::Return) {
            // Handle Enter key event
            if (menu->OnEvent(event)) {
                screen.ExitLoopClosure()();
                return true;
            }
        } 
        if (event == Event::Escape || event == Event::Character('q')) {
            // Exit the loop when Escape or 'q' key is pressed
            screen.ExitLoopClosure()();
            return true;
        }
        return menu->OnEvent(event); // Pass other events to the menu
    });

    // Run the interactive screen loop
    screen.Loop(event_handler);
}

int ScanfOptionView::getSelectedOption() const {
    // Return the currently selected menu option index
    return selected_option;
}

void ScanfOptionView::hideMenu() {
    BaseView::hideMenu(); // Set the view status to hidden
    selected_option = 0;  // Reset the selected option index
    std::system("clear"); // Clear the terminal screen
}

void ScanfOptionView::displayStatusMessage(ScanStatus& status) {
    switch (status) {
        case ScanStatus::SCAN_DIRECTORY_SUCCESS:
            // Display success message for directory scan
            std::cout << "Directory scan successful!\n";
            status = ScanStatus::SCAN_NORMAL;  // Reset status to normal after the message
            break;
        case ScanStatus::SCAN_DIRECTORY_FAILURE:
            // Display failure message for directory scan
            std::cout << "Directory scan failed! Please check the path and try again.\n";
            status = ScanStatus::SCAN_NORMAL;  // Reset status to normal after the message
            break;
        case ScanStatus::SCAN_USB_SUCCESS:
            // Display success message for USB scan
            std::cout << "USB device scan successful!\n";
            status = ScanStatus::SCAN_NORMAL;  // Reset status to normal after the message
            break;
        case ScanStatus::SCAN_USB_FAILURE:
            // Display failure message for USB scan
            std::cout << "USB device scan failed! Device not found.\n";
            status = ScanStatus::SCAN_NORMAL;  // Reset status to normal after the message
            break;
        case ScanStatus::SCAN_NORMAL:
        default:
            // No message is required for the normal state
            break;
    }
}
