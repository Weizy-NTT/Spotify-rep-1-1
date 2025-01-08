#include "ControllerManager.hpp"

// Khởi tạo con trỏ instance tĩnh
ControllerManager* ControllerManager::instance = nullptr;

// Constructor private
ControllerManager::ControllerManager(ViewManager* viewManager, ModelManager* modelManager)
    : views(viewManager), model(modelManager) {
    // Khởi tạo các controller
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
ScanfOptionController ControllerManager::getScanfOptionController() const {
    return *(dynamic_cast<ScanfOptionController*>(controllers[0].get()));
}

PlaylistController ControllerManager::getPlaylistController() const {
    return *(dynamic_cast<PlaylistController*>(controllers[1].get()));
}

MediaFileController ControllerManager::getMediaFileController() const {
    return *(dynamic_cast<MediaFileController*>(controllers[2].get()));
}

PlayingMediaController ControllerManager::getPlayingMediaController() const {
    return *(dynamic_cast<PlayingMediaController*>(controllers[3].get()));
}

DetailedPlaylistController ControllerManager::getDetailedPlaylistController() const {
    return *(dynamic_cast<DetailedPlaylistController*>(controllers[4].get()));
}

MetadataController ControllerManager::getMetadataController() const {
    return *(dynamic_cast<MetadataController*>(controllers[5].get()));
}

ViewManager* ControllerManager::getViewManager() const {
    return views;
}

ModelManager* ControllerManager::getModelManager() const {
    return model;
}
