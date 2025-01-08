#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "DetailedPlaylistView.hpp"
#include "MainMenuView.hpp"
#include "MediaFileView.hpp"
#include "MetadataView.hpp"
#include "PlayingMediaView.hpp"
#include "PlaylistView.hpp"
#include "ScanfOptionView.hpp"
#include <memory>

class ViewManager {
private:
    std::unique_ptr<BaseView> currentView;
    std::vector<std::unique_ptr<BaseView>> views;

public:
    ViewManager();
    void showCurrentView();
    void switchView(std::unique_ptr<BaseView> newView);
    
    ScanfOptionView* getScanfOptionView() const;
    PlaylistView* getPlaylistView() const;
    MediaFileView* getMediaFileView() const;
    PlayingMediaView* getPlayingMediaView() const;
    DetailedPlaylistView* getDetailedPlaylistView() const;
    MetadataView* getMetadataView() const;
};
#endif
