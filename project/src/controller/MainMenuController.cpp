#include "MainMenuController.hpp"
#include "ControllerManager.hpp"

void MainMenuController::handleInput(){
    size_t mainChoice;
    do {
    system("clear");
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_MAIN_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    switch (mainChoice)
        {
        case MainMenu::EXIT: {
            back();
            break;
        }
        case MainMenu::SCAN_OPTIONS: {
            ControllerManager::getInstance()->getScanfOptionController()->handleInput();
            break;
        }
        case MainMenu::ALL_SONGS: {
            ControllerManager::getInstance()->getMediaFileController()->handleInput();
            break;
        }
        case MainMenu::PLAYLIST:{
            ControllerManager::getInstance()->getPlaylistController()->handleInput();
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