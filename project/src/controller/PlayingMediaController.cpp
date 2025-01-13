#include "PlayingMediaController.hpp"
#include "ControllerManager.hpp"

void PlayingMediaController::handleInput(const std::string& ID){
    size_t mainChoice;
    playMediaFile(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID));
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    ControllerManager::getInstance()->getViewManager()->getPlayingMediaView()->showSongInfo(ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->getCurrentMediaFile());
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_PLAYING_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validatePlayingMediaMenu);
    switch (mainChoice)
        {
            case PlayingMediaMenu::BACK_FROM_PLAYING: {
                back();
                break;
            }
            case PlayingMediaMenu::PLAY_PAUSE:{
                play();
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
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->playCurrentTrack();
}

void PlayingMediaController::play(){
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->togglePlayPause();
}

void PlayingMediaController::skipToNext(){
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->nextTrack();
}
void PlayingMediaController::skipToPrevious(){
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->previousTrack();
}
void PlayingMediaController::adjustVolume(int level){

}
void PlayingMediaController::back(){}