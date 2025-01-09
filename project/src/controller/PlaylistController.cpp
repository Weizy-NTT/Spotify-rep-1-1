#include"PlaylistController.hpp"

void PlaylistController::inputFromKeyboard(){
    ControllerManager::getInstance()->getViewManager()->switchView(std::make_unique<PlaylistView>());
    size_t mainChoice;
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    handleInput(mainChoice);
}

void PlaylistController::handleInput(const size_t & input){
    switch (input)
        {
            case PlaylistMenu::SELECT_PLAYLIST:{
                std::string PlaylistID;
                std::cout <<"Enter play list ID for looking: ";
                std::getline(std::cin, PlaylistID);
                showMediafileInList(PlaylistID);
                break;
            }
            case PlaylistMenu::ADD_PLAYLIST:{
                std::string songID;
                std::cout <<"Enter playlist ID for adding: ";
                std::getline(std::cin, songID);
                //addSongToPlaylist(PlaylistName,songID);
            }
                break;
            case PlaylistMenu::REMOVE_PLAYLIST:{
                std::string songID;
                std::cout <<"Enter playlist ID for removing: ";
                std::getline(std::cin, songID);
                //removeSongFromPlaylist(PlaylistName,songID);
            }
                break;
            case PlaylistMenu::BACK_FROM_PLAYLIST:{
                back();
            }
                break;
            default:
                std::cout << "Your choice is not valid\n";
                break;

    }

}
std::vector<Playlist> PlaylistController::getAllPlaylists() const{

}
void PlaylistController::createPlaylist(const std::string& name){

}
void PlaylistController::deletePlaylist(const std::string& name){

}
void PlaylistController::back(){}

void PlaylistController::showMediafileInList(const std::string& listId){
    
}
