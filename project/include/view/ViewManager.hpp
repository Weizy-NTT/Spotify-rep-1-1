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

// Enum for switching between different views
enum SwitchView {
    SW_MAIN_VIEW,         // Switch to the main menu view
    SW_SCANF_VIEW,        // Switch to the scan option view
    SW_PLAYLIST_VIEW,     // Switch to the playlist view
    SW_MEDIAFILE_VIEW,    // Switch to the media file view
    SW_PLAYING_VIEW,      // Switch to the currently playing media view
    SW_DETAILED_VIEW,     // Switch to the detailed playlist view
    SW_METADATA_VIEW      // Switch to the metadata view
};

class ViewManager {
private:
    BaseView* currentView;                               // Pointer to the currently active view
    std::vector<std::unique_ptr<BaseView>> views;       // Collection of all available views

public:
    // Constructor to initialize the view manager
    ViewManager();

    // Display the currently active view
    void showCurrentView();

    // Hide the currently active view
    void hideCurrentView();

    // Switch to a specific view based on the view index
    void switchView(SwitchView viewIndex);

    // Get the scan option view
    ScanfOptionView* getScanfOptionView() const;

    // Get the playlist view
    PlaylistView* getPlaylistView() const;

    // Get the media file view
    MediaFileView* getMediaFileView() const;

    // Get the currently playing media view
    PlayingMediaView* getPlayingMediaView() const;

    // Get the detailed playlist view
    DetailedPlaylistView* getDetailedPlaylistView() const;

    // Get the metadata view
    MetadataView* getMetadataView() const;

    // Get the main menu view
    MainMenuView* getMainMenuView() const;
};

#endif // VIEW_MANAGER_H
