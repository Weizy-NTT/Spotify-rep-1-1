#include "MetadataController.hpp"

void MetadataController::inputFromKeyboard(){
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_METADATA_VIEW);
    size_t mainChoice;
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    handleInput(mainChoice);
}


void MetadataController::handleInput(const size_t& input){
    switch (input)
        {
        case MetadataMenu::BACK_FROM_METADATA: {
            back();
            break;
        }
        case MetadataMenu::EDIT_METADATA:{
            break;
        }
        default:
            std::cout << "Your choice is not valid\n";
            break;
        }
}

std::map<std::string, std::string> MetadataController::getMediaFileMetadata(const MediaFile& file) const{

}
void MetadataController::updateMediaFileMetadata(const MediaFile& file, const std::map<std::string, std::string>& metadata){

}
void MetadataController::back(){
    
}