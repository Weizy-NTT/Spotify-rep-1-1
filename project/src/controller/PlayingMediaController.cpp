#include "PlayingMediaController.hpp"

void PlayingMediaController::inputFromKeyboard(){
    ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<MetadataView>());
    size_t mainChoice;
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    handleInput(mainChoice);
}


void PlayingMediaController::handleInput(const size_t& input){
    switch (input)
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