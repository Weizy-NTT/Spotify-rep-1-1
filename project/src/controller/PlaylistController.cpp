#include"PlaylistController.hpp"
#include "ControllerManager.hpp"

void PlaylistController::handleInput() {
    PlaylistStatus status = PlaylistStatus::PLAYLIST_NORMAL;
    do{
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    showAllPlaylists(ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getAllPlaylists());
    ControllerManager::getInstance()->getViewManager()->getPlaylistView()->displayStatusMessage(status);
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_PLAYLIST_VIEW);
    switch (ControllerManager::getInstance()->getViewManager()->getPlaylistView()->getSelectedOption()) {
        case PlaylistMenu::SELECT_PLAYLIST:{
                std::string PlaylistID;
                Exception_Handler("Enter playlist ID for looking: ",PlaylistID,validateID);
                if (ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->isValidPlaylistIDInLibrary(PlaylistID))
                {
                    ControllerManager::getInstance()->getDetailedPlaylistController()->handleInput(PlaylistID);
                }
                else {
                    status = PlaylistStatus::PLAYLIST_SELECT_STATUS;
                }
                break;
            }
            case PlaylistMenu::ADD_PLAYLIST:{
                std::string playlistName;
                Exception_Handler("Enter playlist name for adding: ",playlistName,validateAlphaSring);
                createPlaylist(playlistName);
                break;
            }
        
            case PlaylistMenu::REMOVE_PLAYLIST:{
                std::string playlistID;
                Exception_Handler("Enter playlist ID for removing: ",playlistID,validateID);
                if (ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->isValidPlaylistIDInLibrary(playlistID))
                {
                    deletePlaylist(playlistID);
                }
                else {
                    status = PlaylistStatus::PLAYLIST_REMOVE_STATUS;
                }
                break;
            }

            case PlaylistMenu::BACK_FROM_PLAYLIST:{
                back();
                break;
            }
        }  
    }while (ControllerManager::getInstance()->getViewManager()->getPlaylistView()->getSelectedOption() != PlaylistMenu::BACK_FROM_PLAYLIST);
}

void PlaylistController::createPlaylist(const std::string& name ){
    std::shared_ptr<Playlist> ptr = std::make_shared<Playlist>(name);
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->addPlaylist(ptr);
}

void PlaylistController::deletePlaylist(const std::string& Id){
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->removePlaylist(Id);
}
void PlaylistController::back(){

}

void PlaylistController::showAllPlaylists(const std::vector<std::shared_ptr<Playlist>>& lists) {
    ControllerManager::getInstance()->getViewManager()->getPlaylistView()->showPlaylistList(lists);
}
