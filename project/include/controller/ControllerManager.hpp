#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include <vector>
#include <memory>
#include "ScanfOptionController.hpp"
#include "PlaylistController.hpp"
#include "MediaFileController.hpp"
#include "PlayingMediaController.hpp"
#include "DetailedPlaylistController.hpp"
#include "MetadataController.hpp"
#include "BaseController.hpp"
#include "ViewManager.hpp"
#include "ModelManager.hpp"
#include "ExceptionLib.hpp"

class ControllerManager {
private:
    static ControllerManager* instance; // Instance duy nhất của lớp
    std::vector<std::unique_ptr<BaseController>> controllers;
    ViewManager* views;
    ModelManager* model;

    // Constructor và destructor private để ngăn tạo đối tượng bên ngoài
    ControllerManager(ViewManager* viewManager, ModelManager* modelManager);
    ~ControllerManager();

public:
    // Xóa copy constructor và operator= để ngăn sao chép
    ControllerManager(const ControllerManager&) = delete;
    ControllerManager& operator=(const ControllerManager&) = delete;

    // Phương thức truy cập instance
    static ControllerManager* getInstance(ViewManager* viewManager = nullptr, ModelManager* modelManager = nullptr);

    ScanfOptionController getScanfOptionController() const;
    PlaylistController getPlaylistController() const;
    MediaFileController getMediaFileController() const;
    PlayingMediaController getPlayingMediaController() const;
    DetailedPlaylistController getDetailedPlaylistController() const;
    MetadataController getMetadataController() const;
    ViewManager* getViewManager() const;
    ModelManager* getModelManager() const;
};

#endif // CONTROLLER_MANAGER_H
