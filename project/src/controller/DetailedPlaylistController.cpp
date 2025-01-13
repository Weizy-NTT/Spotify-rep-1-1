#include "DetailedPlaylistController.hpp"
#include "ControllerManager.hpp"

void DetailedPlaylistController::handleInput(std::string listId){
    size_t mainChoice;
    DetailedPlaylistStatus status = DetailedPlaylistStatus::DETAILED_NORMAL;
    do{
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    showMediafileInList(listId);
    ControllerManager::getInstance()->getViewManager()->getDetailedPlaylistView()->displayStatusMessage(status);
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_DETAILED_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validateDetailedPlaylistMenu);
    switch (mainChoice)
        {
            case DetailedPlaylistMenu::SHOW_DETAIL_SONG:{
                std::string songID;
                Exception_Handler("Enter song ID for looking details: ",songID,validateID);
                if (ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(listId)->isValidMediaFileIDInPlaylist(songID))
                {
                    ControllerManager::getInstance()->getMetadataController()->handleInput(songID);
                }
                else {
                    status = DetailedPlaylistStatus::DETAILED_SHOW_STATUS;
                }
                break;
            }
            case DetailedPlaylistMenu::ADD_SONG:{
                std::string songID;
                Exception_Handler("Enter song ID for adding: ",songID,validateID);
                if (ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->isValidMediaFileIDInLibrary(songID))
                {
                    if (!ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(listId)->isValidMediaFileIDInPlaylist(songID))
                    {
                        addSongToPlaylist(listId,songID);
                    }
                    else {
                        status = DetailedPlaylistStatus::DETAILED_ADD_STATUS;
                    }
                }
                else {
                    status = DetailedPlaylistStatus::DETAILED_ADD_STATUS;
                }
            }
                break;
            case DetailedPlaylistMenu::DELETE_SONG:{
                std::string songID;
                Exception_Handler("Enter song ID for removing: ",songID,validateID);
                if (ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(listId)->isValidMediaFileIDInPlaylist(songID))
                {
                    removeSongFromPlaylist(listId,songID);
                }
                else {
                    status = DetailedPlaylistStatus::DETAILED_DELETE_STATUS;
                }
            }
                break;
            case DetailedPlaylistMenu::BACK_FROM_DETAIL:{
                back();
                break;
            }
            case DetailedPlaylistMenu::PLAY_SONG_FROM_PLAYLIST:{
                std::string songID;
                Exception_Handler("Enter song ID for playing: ",songID,validateID);
                if (ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(listId)->isValidMediaFileIDInPlaylist(songID))
                {
                    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setPlaylist(ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(listId)->getSongs());
                    ControllerManager::getInstance()->getPlayingMediaController()->handleInput(songID);
                }
                else {
                    status = DetailedPlaylistStatus::DETAILED_PLAY_STATUS;
                }
                break;
            }
        }
    }while(mainChoice != DetailedPlaylistMenu::BACK_FROM_DETAIL);
}

void DetailedPlaylistController::addSongToPlaylist(const std::string& PlaylistId, const std::string& songID){
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->addSong((ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(songID)));
}


void DetailedPlaylistController::removeSongFromPlaylist(const std::string& PlaylistId, const std::string& songID){
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->removeSong(songID);
}

void DetailedPlaylistController::back(){
    
}

void DetailedPlaylistController::showMediafileInList(const std::string& listId){
    ControllerManager::getInstance()->getViewManager()->getDetailedPlaylistView()->showListOfSongs(ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(listId));
}



