#include "ViewManager.hpp"
#include <iostream>

ViewManager::ViewManager() {
    // Initialize views
    views.push_back(std::make_unique<ScanfOptionView>());
    views.push_back(std::make_unique<PlaylistView>());
    views.push_back(std::make_unique<MediaFileView>());
    views.push_back(std::make_unique<PlayingMediaView>());
    views.push_back(std::make_unique<DetailedPlaylistView>());
    views.push_back(std::make_unique<MetadataView>());

    currentView = std::make_unique<MainMenuView>();
}

void ViewManager::showCurrentView() {
    if (currentView && !currentView->isShown()) {
        currentView->showMenu();
    }
}

void ViewManager::switchView(std::unique_ptr<BaseView> newView) {
    currentView->hideMenu();
    currentView = std::move(newView);
    showCurrentView();
}

ScanfOptionView* ViewManager::getScanfOptionView() const {
    return dynamic_cast<ScanfOptionView*>(views[0].get());
}

PlaylistView* ViewManager::getPlaylistView() const {
    return dynamic_cast<PlaylistView*>(views[1].get());
}

MediaFileView* ViewManager::getMediaFileView() const {
    return dynamic_cast<MediaFileView*>(views[2].get());
}

PlayingMediaView* ViewManager::getPlayingMediaView() const {
    return dynamic_cast<PlayingMediaView*>(views[3].get());
}

DetailedPlaylistView* ViewManager::getDetailedPlaylistView() const {
    return dynamic_cast<DetailedPlaylistView*>(views[4].get());
}

MetadataView* ViewManager::getMetadataView() const {
    return dynamic_cast<MetadataView*>(views[5].get());
}


