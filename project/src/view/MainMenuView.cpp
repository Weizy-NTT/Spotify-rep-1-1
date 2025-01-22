#include "MainMenuView.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> // For using text, vbox, border
#include <iostream>
using namespace ftxui;

void MainMenuView::showMenu() {
    BaseView::showMenu();
    // Create the menu with predefined entries
    auto menu = Menu(&menu_entries, &selected_option);

    // Create a renderer to display the menu
    auto renderer = Renderer(menu, [&] {
        return vbox({
                   text("===== Main Menu ====="),
                   menu->Render(),
                   text("====================="),
                   text("Use arrow keys or mouse to navigate, press Enter or click to select."),
               }) |
               border;
    });

    // Create a ScreenInteractive object for interaction
    auto screen = ScreenInteractive::TerminalOutput();

    // Handle events
    auto event_handler = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == Mouse::Left && menu->OnEvent(event)) {
                screen.ExitLoopClosure()(); // Exit the loop when a menu item is clicked
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

    // Run the UI loop
    screen.Loop(event_handler);
    // std::system("clear");
}

// Get the selected menu option
int MainMenuView::getSelectedOption() const {
    return selected_option;
}

// Hide the menu and reset the selected option
void MainMenuView::hideMenu() {
    BaseView::hideMenu();
    selected_option = 0;
    std::system("clear");
}
