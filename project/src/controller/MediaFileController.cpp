#include "MediaFileController.hpp"

void MediaFileController::handleInput(){
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_MEDIAFILE_VIEW);
    size_t mainChoice;
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    switch (mainChoice)
        {
        case MediaFileMenu::BACK_FROM_MEDIA: {
            back();
            break;
        }
        case MediaFileMenu::PLAY_SONG_FROM_FILES:{
            break;
        }
           
        case MediaFileMenu::SHOW_DETAIL:{
            break;
        }
        case MediaFileMenu::NEXT_PAGE:{
            break;
        }
        case MediaFileMenu::PREV_PAGE:{
            break;
        }
            
        default:
            std::cout << "Your choice is not valid\n";
            break;
        }
}
std::vector<MediaFile> MediaFileController::getAllMediaFiles() const{

}
MediaFile MediaFileController::getMediaFileDetails(const std::string& name) const{

}

void MediaFileController::back(){}