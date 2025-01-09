#include "MediaFileController.hpp"

void MediaFileController::inputFromKeyboard(){
    handleInput();
}


void MediaFileController::handleInput(){
    size_t mainChoice;
    do {
    displayMediaFilesWithPagination(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getAllMediaFiles());
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_MEDIAFILE_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validatePosInteger);
    switch (mainChoice)
        {
        case MediaFileMenu::BACK_FROM_MEDIA: {
            back();
            break;
        }
        case MediaFileMenu::PLAY_SONG_FROM_FILES:{
            break;
        }
           
        case MediaFileMenu::SHOW_DETAIL:{
            break;
        }
        case MediaFileMenu::NEXT_PAGE:{
            currentPage++;
            break;
        }
        case MediaFileMenu::PREV_PAGE:{
            if (currentPage > 1) {
                currentPage--;
            }
            break;
        }   
        default:
            std::cout << "Your choice is not valid\n";
            break;
        }
    } while(mainChoice != MediaFileMenu::BACK_FROM_MEDIA);
}

// std::vector<MediaFile> MediaFileController::getAllMediaFiles() const{

// }
// MediaFile MediaFileController::getMediaFileDetails(const std::string& name) const{

// }

void MediaFileController::back(){}

void MediaFileController::displayMediaFilesWithPagination(const std::vector<std::shared_ptr<MediaFile>>& files, int pageSize) {
    int totalSongs = files.size();
    //int totalPages = (totalSongs + pageSize - 1) / pageSize;  // Tính số trang cần thiết

    int firstSong = (currentPage - 1) * pageSize;
    int lastSong = std::min(currentPage * pageSize - 1, totalSongs - 1);

    ControllerManager::getInstance()->getViewManager()->getMediaFileView()->showMediaFilesPage(files, currentPage, firstSong, lastSong);

}