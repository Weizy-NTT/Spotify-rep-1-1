#include "PlayingMediaController.hpp"
#include "ControllerManager.hpp"

void PlayingMediaController::handleInput(const std::string& ID){
    size_t mainChoice;
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    playMediaFile(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID));
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_PLAYING_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validatePlayingMediaMenu);
    switch (mainChoice)
        {
            case PlayingMediaMenu::BACK_FROM_PLAYING: {
                back();
                break;
            }
            case PlayingMediaMenu::PLAY_PAUSE:{
                if (ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->getIsPlaying())
                {
                    pause();
                }
                else {
                    play();
                }
                break;
            }
            case PlayingMediaMenu::NEXT:{
                skipToNext();
                break;
            }
            case PlayingMediaMenu::PREV:{
                skipToPrevious();
                break;
            }
        }
    } while(mainChoice != PlayingMediaMenu::BACK_FROM_PLAYING);
}
void PlayingMediaController::playMediaFile(const std::shared_ptr<MediaFile>& file) {
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setCurrentMediaFile(file);
    ControllerManager::getInstance()->getViewManager()->getPlayingMediaView()->showSongInfo(file);
}

void PlayingMediaController::play(){
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setIsPlaying(true);
}
void PlayingMediaController::pause(){
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setIsPlaying(false);
}
void PlayingMediaController::skipToNext(){

}
void PlayingMediaController::skipToPrevious(){

}
void PlayingMediaController::adjustVolume(int level){

}
void PlayingMediaController::back(){}