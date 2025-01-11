#include "ControllerManager.hpp"

// Khởi tạo con trỏ instance tĩnh
ControllerManager* ControllerManager::instance = nullptr;

// Constructor private
ControllerManager::ControllerManager(ViewManager* viewManager, ModelManager* modelManager)
    : views(viewManager), model(modelManager) {
    // Khởi tạo các controller
    controllers.push_back(std::make_unique<MainMenuController>());
    controllers.push_back(std::make_unique<ScanfOptionController>());
    controllers.push_back(std::make_unique<PlaylistController>());
    controllers.push_back(std::make_unique<MediaFileController>());
    controllers.push_back(std::make_unique<PlayingMediaController>());
    controllers.push_back(std::make_unique<DetailedPlaylistController>());
    controllers.push_back(std::make_unique<MetadataController>());
}

// Destructor private
ControllerManager::~ControllerManager() {}

// Phương thức truy cập instance
ControllerManager* ControllerManager::getInstance(ViewManager* viewManager, ModelManager* modelManager) {
    if (instance == nullptr) {
        if (viewManager == nullptr || modelManager == nullptr) {
            throw std::runtime_error("ViewManager và ModelManager không thể null khi khởi tạo ControllerManager.");
        }
        instance = new ControllerManager(viewManager, modelManager);
    }
    return instance;
}

// Các phương thức truy xuất controller

MainMenuController* ControllerManager::getMainMenuController() const {
    if (controllers[modeController::CT_MAIN]) {
        return (dynamic_cast<MainMenuController*>(controllers[modeController::CT_MAIN].get()));
    }
    else {
        return nullptr;
    } 
}

ScanfOptionController* ControllerManager::getScanfOptionController() const {
    if (controllers[modeController::CT_SCANF]) {
        return (dynamic_cast<ScanfOptionController*>(controllers[modeController::CT_SCANF].get()));
    }
    else {
        return nullptr;
    } 
}

PlaylistController* ControllerManager::getPlaylistController() const {
    if (controllers[modeController::CT_PLAYLIST]) {
        return (dynamic_cast<PlaylistController*>(controllers[modeController::CT_PLAYLIST].get()));
    }
    else {
        return nullptr;
    } 
}

MediaFileController* ControllerManager::getMediaFileController() const {
    if (controllers[modeController::CT_MEDIA_FILES]) {
        return (dynamic_cast<MediaFileController*>(controllers[modeController::CT_MEDIA_FILES].get()));
    }
    else {
        return nullptr;
    }
}

PlayingMediaController* ControllerManager::getPlayingMediaController() const {
    if (controllers[modeController::CT_PLAYING_MEDIA]) {
        return (dynamic_cast<PlayingMediaController*>(controllers[modeController::CT_PLAYING_MEDIA].get()));
    }
    else {
        return nullptr;
    }
}

DetailedPlaylistController* ControllerManager::getDetailedPlaylistController() const {
    if (controllers[modeController::CT_DETAILED_PLAYLIST]) {
        return (dynamic_cast<DetailedPlaylistController*>(controllers[modeController::CT_DETAILED_PLAYLIST].get()));
    }
    else {
        return nullptr;
    }
}

MetadataController* ControllerManager::getMetadataController() const {
    if (controllers[modeController::CT_METADATA]) {
        return (dynamic_cast<MetadataController*>(controllers[modeController::CT_METADATA].get()));
    }
    else {
        return nullptr;
    }
}

ViewManager* ControllerManager::getViewManager() const {
    return views;
}

ModelManager* ControllerManager::getModelManager() const {
    return model;
}
