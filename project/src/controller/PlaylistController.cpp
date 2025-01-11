#include"PlaylistController.hpp"
#include "ControllerManager.hpp"

void PlaylistController::handleInput(){
    size_t mainChoice;
    do{
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    showAllPlaylists(ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getAllPlaylists());
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_PLAYLIST_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validatePlaylistsMenu);
    switch (mainChoice)
        {
            case PlaylistMenu::SELECT_PLAYLIST:{
                std::string PlaylistID;
                Exception_Handler("Enter playlist ID for looking: ",PlaylistID,validateID);
                ControllerManager::getInstance()->getDetailedPlaylistController()->handleInput(PlaylistID);
                break;
            }
            case PlaylistMenu::ADD_PLAYLIST:{
                std::string playlistID, playlistName;
                Exception_Handler("Enter playlist ID for adding: ",playlistID,validateID);
                Exception_Handler("Enter playlist name for adding: ",playlistName,validateAlphaSring);
                createPlaylist(playlistID, playlistName);
                break;
            }
        
            case PlaylistMenu::REMOVE_PLAYLIST:{
                std::string playlistID;
                Exception_Handler("Enter playlist ID for removing: ",playlistID,validateID);
                deletePlaylist(playlistID);
                break;
            }

            case PlaylistMenu::BACK_FROM_PLAYLIST:{
                back();
                break;
            }
        }
    }while (mainChoice != PlaylistMenu::BACK_FROM_PLAYLIST);
    
}

void PlaylistController::createPlaylist(const std::string& id, const std::string& name ){
    std::shared_ptr<Playlist> ptr = std::make_shared<Playlist>(id, name);
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->addPlaylist(ptr);
}

void PlaylistController::deletePlaylist(const std::string& Id){
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->removePlaylist(Id);
}
void PlaylistController::back(){

}

void PlaylistController::showMediafileInList(const std::string& listId){
    ControllerManager::getInstance()->getViewManager()->getDetailedPlaylistView()->showListOfSongs(ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(listId));
}

void PlaylistController::showAllPlaylists(const std::vector<std::shared_ptr<Playlist>>& lists) {
    ControllerManager::getInstance()->getViewManager()->getPlaylistView()->showPlaylistList(lists);
}
