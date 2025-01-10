#include "DetailedPlaylistController.hpp"

void DetailedPlaylistController::handleInput(std::string listId){
    size_t mainChoice;
    do{
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    ControllerManager::getInstance()->getPlaylistController()->showMediafileInList(listId);
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_DETAILED_VIEW);

    break;
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    switch (mainChoice)
        {
            case DetailedPlaylistMenu::SHOW_DETAIL_SONG:{
                std::string songID;
                std::cout <<"Enter play song ID for looking details: ";
                std::getline(std::cin, songID);
                showDetailSong(listId,songID);
                break;
            }
            case DetailedPlaylistMenu::ADD_SONG:{
                std::string songID;
                std::cout <<"Enter play song ID for adding: ";
                std::getline(std::cin, songID);
                addSongToPlaylist(listId,songID);
            }
                break;
            case DetailedPlaylistMenu::DELETE_SONG:{
                std::string songID;
                std::cout <<"Enter play song ID for removing: ";
                std::getline(std::cin, songID);
                ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(listId)->removeSong(songID);
            }
                break;
            case DetailedPlaylistMenu::BACK_FROM_DETAIL:{
                back();
                break;
            }
            case DetailedPlaylistMenu::PLAY_SONG_FROM_PLAYLIST:{
                std::string songID;
                std::cout <<"Enter play song ID for playing: ";
                std::getline(std::cin, songID);
                playSong(songID);
                break;
            }

            default:
                std::cout << "Your choice is not valid\n";
                break;

    }
    }while(mainChoice != DetailedPlaylistMenu::BACK_FROM_DETAIL);
}

void DetailedPlaylistController::showDetailSong(const std::string& PlaylistId, const std::string& songID){
    ControllerManager::getInstance()->getViewManager()->getMetadataView()->showFileMetadata((ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->getSongByID(songID)));
}

void DetailedPlaylistController::addSongToPlaylist(const std::string& PlaylistId, const std::string& songID){
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->addSong((ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->getSongByID(songID)));
}


void DetailedPlaylistController::removeSongFromPlaylist(const std::string& PlaylistId, const std::string& songID){
    ControllerManager::getInstance()->getModelManager()->getPlaylistLibrary()->getPlaylistByID(PlaylistId)->removeSong(songID);
}

void DetailedPlaylistController::back(){
    
}

void DetailedPlaylistController::playSong(const std::string songID){

}

