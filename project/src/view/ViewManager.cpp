#include "ViewManager.hpp"
#include <iostream>

ViewManager::ViewManager() {
    // Initialize views
    views.push_back(std::make_unique<MainMenuView>());
    views.push_back(std::make_unique<ScanfOptionView>());
    views.push_back(std::make_unique<PlaylistView>());
    views.push_back(std::make_unique<MediaFileView>());
    views.push_back(std::make_unique<PlayingMediaView>());
    views.push_back(std::make_unique<DetailedPlaylistView>());
    views.push_back(std::make_unique<MetadataView>());

    currentView = views[SwitchView::SW_MAIN_VIEW].get();
}

void ViewManager::showCurrentView() {
    if (currentView && !currentView->isShown()) {
        currentView->showMenu();
    }
}

void ViewManager::switchView(SwitchView viewIndex) {
    currentView->hideMenu();
    currentView = views[viewIndex].get();
    showCurrentView();
}

MainMenuView* ViewManager::getMainMenuView() const {
    return dynamic_cast<MainMenuView*>(views[SwitchView::SW_MAIN_VIEW].get());
}

ScanfOptionView* ViewManager::getScanfOptionView() const {
    return dynamic_cast<ScanfOptionView*>(views[SwitchView::SW_SCANF_VIEW].get());
}

PlaylistView* ViewManager::getPlaylistView() const {
    return dynamic_cast<PlaylistView*>(views[SwitchView::SW_PLAYLIST_VIEW].get());
}
MediaFileView* ViewManager::getMediaFileView() const {
    return dynamic_cast<MediaFileView*>(views[SwitchView::SW_MEDIAFILE_VIEW].get());
}

PlayingMediaView* ViewManager::getPlayingMediaView() const {
    return dynamic_cast<PlayingMediaView*>(views[SwitchView::SW_PLAYING_VIEW].get());
}

DetailedPlaylistView* ViewManager::getDetailedPlaylistView() const {
    return dynamic_cast<DetailedPlaylistView*>(views[SwitchView::SW_DETAILED_VIEW].get());
}

MetadataView* ViewManager::getMetadataView() const {
    return dynamic_cast<MetadataView*>(views[SwitchView::SW_METADATA_VIEW].get());
}


