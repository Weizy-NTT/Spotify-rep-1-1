#include "MediaFileController.hpp"
#include "ControllerManager.hpp"

void MediaFileController::handleInput(){
    size_t mainChoice;
    size_t totalPage = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getAllMediaFiles().size();
    totalPage = (size_t)(totalPage/25) + 1;
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
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
            std::string songID;
            std::cout <<"Enter play song ID for looking details: ";
            std::getline(std::cin, songID);
            ControllerManager::getInstance()->getMetadataController()->handleInput(songID);
            break;
        }
        case MediaFileMenu::NEXT_PAGE:{
            if (currentPage < totalPage) {
                currentPage++;
            }
            else {
                std::cout << "This is the last page\n";
            }
            break;
        }
        case MediaFileMenu::PREV_PAGE:{
            if (currentPage > 1) {
                currentPage--;
            }
            else {
                std::cout << "This is the first page\n";
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

void MediaFileController::back(){}

void MediaFileController::displayMediaFilesWithPagination(const std::vector<std::shared_ptr<MediaFile>>& files, size_t pageSize) {
    size_t totalSongs = files.size();
    //int totalPages = (totalSongs + pageSize - 1) / pageSize;  // Tính số trang cần thiết

    size_t firstSong = (currentPage - 1) * pageSize;
    size_t lastSong = std::min(currentPage * pageSize - 1, totalSongs - 1);

    ControllerManager::getInstance()->getViewManager()->getMediaFileView()->showMediaFilesPage(files, currentPage, firstSong, lastSong);

}