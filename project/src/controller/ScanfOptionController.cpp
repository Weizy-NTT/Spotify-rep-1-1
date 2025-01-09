#include "ScanfOptionController.hpp"
#include <iostream>
#include "ScanfOptionView.hpp"
#include "ControllerManager.hpp"

void ScanfOptionController::inputFromKeyboard(){
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_SCANF_VIEW);
    size_t mainChoice;
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    handleInput(mainChoice);
}
void ScanfOptionController::handleInput(const size_t& input){
    switch (input)
        {
        case ScanfMenu::BACK_FROM_SCAN: {
            back();
            break;
        }
        case ScanfMenu::SCANF_DIRECTORY:{
            std::string path;
            std::cout<<"Enter your path you want to scan: ";
            std::getline(std::cin, path);
            scanDirectory(path);
            break;
        }
           
        case ScanfMenu::SCANF_USB:{
            std::string path;
            std::cout<<"Enter your path you want to scan from usb: ";
            std::getline(std::cin, path);
            scanDirectory(path);
            break;
        }
            
        default:
            std::cout << "Your choice is not valid\n";
            break;
        }


}
std::vector<MediaFile> ScanfOptionController::scanDirectory(const std::string& path){

}
std::vector<MediaFile> ScanfOptionController::scanUSBDevice(){

}

void ScanfOptionController::back(){

}