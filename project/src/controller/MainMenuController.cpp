#include "MainMenuController.hpp"
#include "ControllerManager.hpp"

void MainMenuController::handleInput(){
    //ControllerManager::getInstance()->getHardwareController()->threadReading();
    bool status = false;
    std::string filePath = "resources/playlists.txt";
    ControllerManager::getInstance()->getScanfOptionController()->scanPlaylistsFromTxt(filePath);
    size_t mainChoice;
    do {
    system("clear");
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    if (status) {
        std::cout << "No current mediafile playing\n";
        status = false;
    }
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
            case MainMenu::NOW_PLAYING:{
                if (ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->getCurrentMediaFile())
                {
                std::string ID = ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->getCurrentMediaFile()->getID();
                ControllerManager::getInstance()->getPlayingMediaController()->handleInput(ID);
                }
                else {
                    status = true;
                }
                break;
            }
        }
    } while(mainChoice != MainMenu::EXIT);
}

void MainMenuController::back(){
    std::string filePath = "resources/playlists.txt";
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->saveToFile(filePath);
    //ControllerManager::getInstance()->getHardwareController()->stopReading();
    std::exit(0);
}