#include "DetailedPlaylistController.hpp"

void DetailedPlaylistController::inputFromKeyboard(){
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_DETAILED_VIEW);
    size_t mainChoice;
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    handleInput(mainChoice);
}

void DetailedPlaylistController::handleInput(const size_t & input){

    switch (input)
        {
            case DetailedPlaylistMenu::SHOW_DETAIL_SONG:{
                //getPlaylistDetails(PlaylistName);
                break;
            }
            case DetailedPlaylistMenu::ADD_SONG:{
                std::string songID;
                std::cout <<"Enter play song ID for plaing: ";
                std::getline(std::cin, songID);
                //addSongToPlaylist(PlaylistName,songID);
            }
                break;
            case DetailedPlaylistMenu::DELETE_SONG:{
                std::string songID;
                std::cout <<"Enter play song ID for removing: ";
                std::getline(std::cin, songID);
                //removeSongFromPlaylist(PlaylistName,songID);
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
}


Playlist DetailedPlaylistController::getPlaylistDetails(const std::string& playlistName) const{

}

void DetailedPlaylistController::addSongToPlaylist(const std::string& playlistName, const std::string songID){

}

void DetailedPlaylistController::removeSongFromPlaylist(const std::string& playlistName, const std::string songID){

}

void DetailedPlaylistController::back(){}

void DetailedPlaylistController::playSong(const std::string songID){

}

