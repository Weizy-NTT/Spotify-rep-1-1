#include "ViewManager.hpp"
#include "ModelManager.hpp"
#include "ControllerManager.hpp"
#include <iostream>
#include "ExceptionLib.hpp"

int main() {

    while(1) {
        ControllerManager::getInstance(new ViewManager,new ModelManager)->getViewManager()->showCurrentView();
        size_t mainChoice;
        Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);

        switch (mainChoice)
        {
        case MainMenu::SCAN_OPTIONS: {
            ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<ScanfOptionView>());
            size_t scanfChoice;
            std::string path;
            Exception_Handler("Enter your choice: ",scanfChoice,validatePosInteger);
            switch (scanfChoice) {
                case ScanfMenu::SCANF_DIRECTORY:
                    Exception_Handler("Enter directory path: ",path,validateFullName);
                    ControllerManager::getInstance()->getModelManager()->getMediaLibrary().setAllMediaFiles(ControllerManager::getInstance()->getScanfOptionController().scanDirectory(path));
                    break;
                case ScanfMenu::SCANF_USB:
                    break;
                case ScanfMenu::BACK_FROM_SCAN:
                    break;
                default:
                    std::cout << "Your choice is not valid\n";
                    break;
            }
            break;
        }
        case MainMenu::ALL_SONGS:
            ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<MediaFileView>());
            break;
        case MainMenu::PLAYLIST:
            ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<PlaylistView>());
            break;
        case MainMenu::EXIT:
            std::cout << "Exiting the program....\n";
            return 0;
        default:
            std::cout << "Your choice is not valid\n";
            break;
        }
        ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<MainMenuView>());
    }
    return 0;
}