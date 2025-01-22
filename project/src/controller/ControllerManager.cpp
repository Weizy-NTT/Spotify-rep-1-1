#include "ControllerManager.hpp"

// Initialize the static instance pointer
ControllerManager* ControllerManager::instance = nullptr;

// Private constructor
ControllerManager::ControllerManager(ViewManager* viewManager, ModelManager* modelManager)
    : views(viewManager), model(modelManager) {
    controllers.push_back(std::make_unique<MainMenuController>()); 
    controllers.push_back(std::make_unique<ScanfOptionController>()); 
    controllers.push_back(std::make_unique<PlaylistController>()); 
    controllers.push_back(std::make_unique<MediaFileController>()); 
    controllers.push_back(std::make_unique<PlayingMediaController>()); 
    controllers.push_back(std::make_unique<DetailedPlaylistController>()); 
    controllers.push_back(std::make_unique<MetadataController>()); 
    controllers.push_back(std::make_unique<HardwareController>("/dev/ttyACM0", 9600)); 
}

// Private destructor
ControllerManager::~ControllerManager() {}

// Method to access the singleton instance
// Ensures that there is only one instance of ControllerManager and initializes it if necessary
ControllerManager* ControllerManager::getInstance(ViewManager* viewManager, ModelManager* modelManager) {
    if (instance == nullptr) {
        if (viewManager == nullptr || modelManager == nullptr) {
            throw std::runtime_error("ViewManager and ModelManager cannot be null when initializing ControllerManager.");
        }
        instance = new ControllerManager(viewManager, modelManager);
    }
    return instance;
}

// Methods to access individual controllers
// Returns a pointer to the MainMenuController if it exists, otherwise returns nullptr
MainMenuController* ControllerManager::getMainMenuController() const {
    if (controllers[modeController::CT_MAIN]) {
        return (dynamic_cast<MainMenuController*>(controllers[modeController::CT_MAIN].get()));
    } else {
        return nullptr;
    }
}

// Returns a pointer to the ScanfOptionController if it exists, otherwise returns nullptr
ScanfOptionController* ControllerManager::getScanfOptionController() const {
    if (controllers[modeController::CT_SCANF]) {
        return (dynamic_cast<ScanfOptionController*>(controllers[modeController::CT_SCANF].get()));
    } else {
        return nullptr;
    }
}

// Returns a pointer to the PlaylistController if it exists, otherwise returns nullptr
PlaylistController* ControllerManager::getPlaylistController() const {
    if (controllers[modeController::CT_PLAYLIST]) {
        return (dynamic_cast<PlaylistController*>(controllers[modeController::CT_PLAYLIST].get()));
    } else {
        return nullptr;
    }
}

// Returns a pointer to the MediaFileController if it exists, otherwise returns nullptr
MediaFileController* ControllerManager::getMediaFileController() const {
    if (controllers[modeController::CT_MEDIA_FILES]) {
        return (dynamic_cast<MediaFileController*>(controllers[modeController::CT_MEDIA_FILES].get()));
    } else {
        return nullptr;
    }
}

// Returns a pointer to the PlayingMediaController if it exists, otherwise returns nullptr
PlayingMediaController* ControllerManager::getPlayingMediaController() const {
    if (controllers[modeController::CT_PLAYING_MEDIA]) {
        return (dynamic_cast<PlayingMediaController*>(controllers[modeController::CT_PLAYING_MEDIA].get()));
    } else {
        return nullptr;
    }
}

// Returns a pointer to the DetailedPlaylistController if it exists, otherwise returns nullptr
DetailedPlaylistController* ControllerManager::getDetailedPlaylistController() const {
    if (controllers[modeController::CT_DETAILED_PLAYLIST]) {
        return (dynamic_cast<DetailedPlaylistController*>(controllers[modeController::CT_DETAILED_PLAYLIST].get()));
    } else {
        return nullptr;
    }
}

// Returns a pointer to the MetadataController if it exists, otherwise returns nullptr
MetadataController* ControllerManager::getMetadataController() const {
    if (controllers[modeController::CT_METADATA]) {
        return (dynamic_cast<MetadataController*>(controllers[modeController::CT_METADATA].get()));
    } else {
        return nullptr;
    }
}

// Returns a pointer to the HardwareController if it exists, otherwise returns nullptr
HardwareController* ControllerManager::getHardwareController() const {
    if (controllers[modeController::CT_HARDWARE]) {
        return (dynamic_cast<HardwareController*>(controllers[modeController::CT_HARDWARE].get()));
    } else {
        return nullptr;
    }
}

// Returns a pointer to the ViewManager
ViewManager* ControllerManager::getViewManager() const {
    return views;
}

// Returns a pointer to the ModelManager
ModelManager* ControllerManager::getModelManager() const {
    return model;
}
