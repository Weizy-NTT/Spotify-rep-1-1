#include "DetailedPlaylistController.hpp"
#include "ControllerManager.hpp"

void DetailedPlaylistController::handleInput(std::string listId){
    size_t mainChoice;
    do{
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    ControllerManager::getInstance()->getPlaylistController()->showMediafileInList(listId);
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_DETAILED_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validateDetailedPlaylistMenu);
    switch (mainChoice)
        {
            case DetailedPlaylistMenu::SHOW_DETAIL_SONG:{
                std::string songID;
                Exception_Handler("Enter song ID for looking details: ",songID,validateID);
                showDetailSong(listId,songID);
                break;
            }
            case DetailedPlaylistMenu::ADD_SONG:{
                std::string songID;
                Exception_Handler("Enter song ID for adding: ",songID,validateID);
                addSongToPlaylist(listId,songID);
            }
                break;
            case DetailedPlaylistMenu::DELETE_SONG:{
                std::string songID;
                Exception_Handler("Enter song ID for removing: ",songID,validateID);
                removeSongFromPlaylist(listId,songID);
            }
                break;
            case DetailedPlaylistMenu::BACK_FROM_DETAIL:{
                back();
                break;
            }
            case DetailedPlaylistMenu::PLAY_SONG_FROM_PLAYLIST:{
                std::string songID;
                Exception_Handler("Enter song ID for playing: ",songID,validateID);
                ControllerManager::getInstance()->getPlayingMediaController()->handleInput(songID);
                break;
            }
        }
    }while(mainChoice != DetailedPlaylistMenu::BACK_FROM_DETAIL);
}

void DetailedPlaylistController::showDetailSong(const std::string& PlaylistId, const std::string& songID){
    ControllerManager::getInstance()->getViewManager()->getMetadataView()->showFileMetadata((ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->getSongByID(songID)));
}

void DetailedPlaylistController::addSongToPlaylist(const std::string& PlaylistId, const std::string& songID){
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->addSong((ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(songID)));
}


void DetailedPlaylistController::removeSongFromPlaylist(const std::string& PlaylistId, const std::string& songID){
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->removeSong(songID);
}

void DetailedPlaylistController::back(){
    
}


