#include "PlayingMediaController.hpp"
#include "ControllerManager.hpp"
#include <condition_variable>

std::mutex cvMutex;

void PlayingMediaController::handleInput(const std::string& ID){
    isPlayingView.store(true, std::memory_order_relaxed);
    size_t mainChoice;
    playMediaFile(ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getMediaFileByID(ID));
    do {
    updateTime();
    Exception_Handler("Enter your choice: ",mainChoice,validatePlayingMediaMenu);
    switch (mainChoice)
        {
            case PlayingMediaMenu::BACK_FROM_PLAYING: {
                back();
                break;
            }
            case PlayingMediaMenu::PLAY:{
                play();
                break;
            }
            case PlayingMediaMenu::PAUSE:{
                pause();
                break;
            }
            case PlayingMediaMenu::NEXT:{
                skipToNext();
                break;
            }
            case PlayingMediaMenu::PREV:{
                skipToPrevious();
                break;
            }
            case PlayingMediaMenu::VOLUME:{
                size_t volume;
                Exception_Handler("Enter new volume(0 to 128): ",volume,validateVolume);
                adjustVolume(volume);
                break;
            }
        }
    } while(mainChoice != PlayingMediaMenu::BACK_FROM_PLAYING);
}

void PlayingMediaController::playMediaFile(const std::shared_ptr<MediaFile>& file) {
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setCurrentMediaFile(file);
    startUpdateThread();
}

void PlayingMediaController::play() {
    auto playingMedia = ControllerManager::getInstance()->getModelManager()->getPlayingMedia();
    playingMedia->resumeMusic();
}

void PlayingMediaController::pause() {
    auto playingMedia = ControllerManager::getInstance()->getModelManager()->getPlayingMedia();
    playingMedia->pauseMusic();
}

void PlayingMediaController::skipToNext(){
    stopUpdateThread();
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->nextTrack();
    startUpdateThread();
}

void PlayingMediaController::skipToPrevious(){
    stopUpdateThread();
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->previousTrack();
    startUpdateThread();
}

void PlayingMediaController::adjustVolume(size_t level){
    ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->adjustVolume(level);
}

void PlayingMediaController::updateTime() {
    ControllerManager::getInstance()->getViewManager()->hideCurrentView();
    size_t current = ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->getCurrentTime();
    size_t total = ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->getTotalTime();
    ControllerManager::getInstance()->getViewManager()->getPlayingMediaView()->showSongInfo(ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->getCurrentMediaFile(),current,total);
    ControllerManager::getInstance()->getViewManager()->switchView(SwitchView::SW_PLAYING_VIEW);
}

void PlayingMediaController::back(){
    isPlayingView.store(false, std::memory_order_relaxed);
}

void PlayingMediaController::updateElapsedTime() {
    auto playing = ControllerManager::getInstance()->getModelManager()->getPlayingMedia();

    while (isPlayingMediaFile.load(std::memory_order_relaxed)) {
        // Cập nhật thời gian phát nhạc
        std::this_thread::sleep_for(std::chrono::seconds(1));
        playing->setCurrentTime(playing->getCurrentTime() + 1);

        if (isPlayingView.load(std::memory_order_relaxed)) {
            updateTime();  // Cập nhật giao diện nếu cần
        }

        if (playing->getCurrentTime() >= playing->getTotalTime()) {
            playing->nextTrack();
            if (!playing->getCurrentMediaFile()) {  // Hết playlist
                isPlayingMediaFile.store(false, std::memory_order_relaxed);
            }
        }
    }
}


void PlayingMediaController::startUpdateThread() {
    if (!isPlayingMediaFile.load(std::memory_order_relaxed)) {
        isPlayingMediaFile.store(true, std::memory_order_relaxed);
        if (!updateThread.joinable()) {  // Nếu thread chưa chạy, khởi động
            updateThread = std::thread(&PlayingMediaController::updateElapsedTime, this);
        }
    }
}

void PlayingMediaController::stopUpdateThread() {
    if (isPlayingMediaFile.load(std::memory_order_relaxed)) {
        isPlayingMediaFile.store(false, std::memory_order_relaxed);
        if (updateThread.joinable()) {
            updateThread.join();
        }
    }
}


