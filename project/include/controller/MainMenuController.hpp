#ifndef MAIN_MENU_CONTROLLER_H
#define MAIN_MENU_CONTROLLER_H

#include "BaseController.hpp"

class MainMenuController : public BaseController {
public:
    // Handle user input in the main menu
    void handleInput();

    // Navigate back to the previous menu or screen
    void back();
};

#endif // MAIN_MENU_CONTROLLER_H