#include "MediaFileController.hpp"
#include "ControllerManager.hpp"

void MediaFileController::handleInput(){
    size_t mainChoice;
    MediaFileStatus status = MediaFileStatus::MEDIAFILE_NORMAL;
    size_t totalPage = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getAllMediaFiles().size();
    totalPage = (size_t)(totalPage/25) + 1;
    do {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    displayMediaFilesWithPagination(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getAllMediaFiles());
    ControllerManager::getInstance()->getViewManager()->getMediaFileView()->displayStatusMessage(status);
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_MEDIAFILE_VIEW);
    Exception_Handler("Enter your choice: ",mainChoice,validateMediaFilesMenu);
    switch (mainChoice)
        {
        case MediaFileMenu::BACK_FROM_MEDIA: {
            back();
            break;
        }
        case MediaFileMenu::PLAY_SONG_FROM_FILES:{
            std::string songID;
            Exception_Handler("Enter song ID for playing: ",songID,validateID);
            if (ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->isValidMediaFileIDInLibrary(songID))
            {
                ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setPlaylist(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getAllMediaFiles());
                ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setPlayingView(true);
                ControllerManager::getInstance()->getPlayingMediaController()->handleInput(songID);
            }
            else {
                status = MediaFileStatus::MEDIAFILE_PLAY_STATUS;
            }
            break;
        }
           
        case MediaFileMenu::SHOW_DETAIL:{
            std::string songID;
            Exception_Handler("Enter song ID for looking details: ",songID,validateID);
            if (ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->isValidMediaFileIDInLibrary(songID))
            {
                ControllerManager::getInstance()->getMetadataController()->handleInput(songID);
            }
            else {
                status = MediaFileStatus::MEDIAFILE_DETAIL_STATUS;
            }
            break;
        }
        case MediaFileMenu::NEXT_PAGE:{
            if (currentPage < totalPage) {
                currentPage++;
            }
            else {
                status = MediaFileStatus::MEDIAFILE_NEXT_PAGE_STATUS;
            }
            break;
        }
        case MediaFileMenu::PREV_PAGE:{
            if (currentPage > 1) {
                currentPage--;
            }
            else {
                status = MediaFileStatus::MEDIAFILE_PREV_PAGE_STATUS;
            }
            break;
        }   
        }
    } while(mainChoice != MediaFileMenu::BACK_FROM_MEDIA);
}

void MediaFileController::back(){}

void MediaFileController::displayMediaFilesWithPagination(const std::vector<std::shared_ptr<MediaFile>>& files, size_t pageSize) {
    size_t totalSongs = files.size();
    //int totalPages = (totalSongs + pageSize - 1) / pageSize;  // Tính số trang cần thiết

    size_t firstSong = (currentPage - 1) * pageSize;
    size_t lastSong = std::min(currentPage * pageSize - 1, totalSongs - 1);

    ControllerManager::getInstance()->getViewManager()->getMediaFileView()->showMediaFilesPage(files, currentPage, firstSong, lastSong);

}