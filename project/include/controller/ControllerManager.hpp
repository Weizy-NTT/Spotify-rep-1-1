#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include <iostream>
#include <vector>
#include <memory>
#include "ScanfOptionController.hpp"
#include "PlaylistController.hpp"
#include "MediaFileController.hpp"
#include "PlayingMediaController.hpp"
#include "DetailedPlaylistController.hpp"
#include "MetadataController.hpp"
#include "BaseController.hpp"
#include "HardwareController.hpp"
#include "ViewManager.hpp"
#include "ModelManager.hpp"
#include "ExceptionLib.hpp"
#include "MainMenuController.hpp"

// Enumeration for controller modes
enum modeController {
    CT_MAIN,               // Main menu controller
    CT_SCANF,              // Scanf option controller
    CT_PLAYLIST,           // Playlist controller
    CT_MEDIA_FILES,        // Media files controller
    CT_PLAYING_MEDIA,      // Currently playing media controller
    CT_DETAILED_PLAYLIST,  // Detailed playlist controller
    CT_METADATA,           // Metadata controller
    CT_HARDWARE            // Hardware controller
};

class ControllerManager {
private:
    static ControllerManager* instance; // Singleton instance of this class
    std::vector<std::unique_ptr<BaseController>> controllers; // List of controllers
    ViewManager* views; // Pointer to the view manager
    ModelManager* model; // Pointer to the model manager

    // Private constructor and destructor to restrict object creation
    ControllerManager(ViewManager* viewManager, ModelManager* modelManager);
    ~ControllerManager();

public:
    // Delete copy constructor and assignment operator to avoid copying
    ControllerManager(const ControllerManager&) = delete;
    ControllerManager& operator=(const ControllerManager&) = delete;

    // Accessor for the singleton instance
    static ControllerManager* getInstance(ViewManager* viewManager = nullptr, ModelManager* modelManager = nullptr);

    MainMenuController* getMainMenuController() const;                 // Retrieve the main menu controller
    ScanfOptionController* getScanfOptionController() const;           // Retrieve the scanf option controller
    PlaylistController* getPlaylistController() const;                 // Retrieve the playlist controller
    MediaFileController* getMediaFileController() const;               // Retrieve the media file controller
    PlayingMediaController* getPlayingMediaController() const;         // Retrieve the currently playing media controller
    DetailedPlaylistController* getDetailedPlaylistController() const; // Retrieve the detailed playlist controller
    MetadataController* getMetadataController() const;                 // Retrieve the metadata controller
    ViewManager* getViewManager() const;                               // Retrieve the view manager
    ModelManager* getModelManager() const;                             // Retrieve the model manager
    HardwareController* getHardwareController() const;                 // Retrieve the hardware controller
};

#endif // CONTROLLER_MANAGER_H
