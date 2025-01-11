#include"PlaylistController.hpp"
#include "ControllerManager.hpp"

void PlaylistController::handleInput(){
    size_t mainChoice;
    do{
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    showAllPlaylists(ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getAllPlaylists());
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_PLAYLIST_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    switch (mainChoice)
        {
            case PlaylistMenu::SELECT_PLAYLIST:{
                std::string PlaylistID;
                std::cout <<"Enter play list ID for looking: ";
                std::getline(std::cin, PlaylistID);
                ControllerManager::getInstance()->getDetailedPlaylistController()->handleInput(PlaylistID);
                break;
            }
            case PlaylistMenu::ADD_PLAYLIST:{
                std::string playlistID, playlistName;
                std::cout <<"Enter playlist ID for adding: ";
                std::getline(std::cin, playlistID);
                std::cout <<"Enter playlist name for adding: ";
                std::getline(std::cin, playlistName);
                createPlaylist(playlistID, playlistName);
                break;
            }
        
            case PlaylistMenu::REMOVE_PLAYLIST:{
                std::string PlaylistName;
                std::cout <<"Enter playlist ID for removing: ";
                std::getline(std::cin, PlaylistName);
                deletePlaylist(PlaylistName);
                break;
            }

            case PlaylistMenu::BACK_FROM_PLAYLIST:{
                back();
                break;
            }
            default:
                std::cout << "Your choice is not valid\n";
                break;

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
