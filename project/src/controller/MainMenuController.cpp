#include "MainMenuController.hpp"
#include "ControllerManager.hpp"

void MainMenuController::handleInput(){
    std::string filePath = "resources/playlists.txt";
    ControllerManager::getInstance()->getScanfOptionController()->scanPlaylistsFromTxt(filePath);
    size_t mainChoice;
    do {
    system("clear");
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_MAIN_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validateMainMenu);
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
        }
    } while(mainChoice != MainMenu::EXIT);
     ControllerManager::getInstance()->finalize();
}

void MainMenuController::back(){
    td::string filePath = "resources/playlists.txt";
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->saveToFile(filePath);
    std::exit(0);
}