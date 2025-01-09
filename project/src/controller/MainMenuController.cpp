#include "MainMenuController.hpp"
#include "ControllerManager.hpp"

void MainMenuController::inputFromKeyboard(){
    handleInput();
}
void MainMenuController::handleInput(){
    size_t mainChoice;
    do {
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_MAIN_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    switch (mainChoice)
        {
        case MainMenu::EXIT: {
            back();
            break;
        }
        case MainMenu::SCAN_OPTIONS: {
            ControllerManager::getInstance()->getScanfOptionController()->inputFromKeyboard();
            break;
        }
        case MainMenu::ALL_SONGS: {
            ControllerManager::getInstance()->getMediaFileController()->inputFromKeyboard();
            break;
        }
           
        case MainMenu::PLAYLIST:{
            break;
        }
        default:
            std::cout << "Invalid input\n";
        }
    } while(mainChoice != MainMenu::EXIT);
}

void MainMenuController::back(){
    std::exit(0);
}