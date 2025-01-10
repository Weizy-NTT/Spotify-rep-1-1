#include "MetadataController.hpp"
#include "ControllerManager.hpp"

void MetadataController::handleInput(const std::string& ID){
    size_t mainChoice;
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    getMediaFileMetadata(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID));
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_METADATA_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    switch (mainChoice)
        {
        case MetadataMenu::BACK_FROM_METADATA: {
            back();
            break;
        }
        case MetadataMenu::EDIT_METADATA:{
            std::string key, value;
            std::cout <<"Enter the key: ";
            std::getline(std::cin, key);
            std::cout <<"Enter the value: ";
            std::getline(std::cin, value);
            updateMediaFileMetadata(key, value, ID);
            break;
        }
        default:
            std::cout << "Your choice is not valid\n";
            break;
        }
    } while(mainChoice != MetadataMenu::BACK_FROM_METADATA);
}

void MetadataController::getMediaFileMetadata(const std::shared_ptr<MediaFile>& file) const{
    ControllerManager::getInstance()->getViewManager()->getMetadataView()->showFileMetadata(file);
}

void MetadataController::updateMediaFileMetadata(const std::string& key, const std::string& value,const std::string& ID){
    ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID)->getMetadata().setValue(key,value);
}
void MetadataController::back(){
    
}
