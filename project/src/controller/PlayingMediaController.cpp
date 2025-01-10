#include "PlayingMediaController.hpp"

void PlayingMediaController::handleInput(){
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_PLAYING_VIEW);
    size_t mainChoice;
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    switch (mainChoice)
        {
        case PlayingMediaMenu::BACK_FROM_PLAYING: {
            break;
        }
        case PlayingMediaMenu::PLAY_PAUSE:{
            break;
        }
        case PlayingMediaMenu::NEXT:{
            break;
        }
        case PlayingMediaMenu::PREV:{
            break;
        }
        default:
            std::cout << "Your choice is not valid\n";
            break;
        }
}
void PlayingMediaController::playMediaFile(MediaFile file){

}
void PlayingMediaController::play(){

}
void PlayingMediaController::pause(){

}
void PlayingMediaController::skipToNext(){

}
void PlayingMediaController::skipToPrevious(){

}
void PlayingMediaController::adjustVolume(int level){

}
void PlayingMediaController::back(){}