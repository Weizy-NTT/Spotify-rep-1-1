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

enum modeController {
    CT_MAIN,
    CT_SCANF,
    CT_PLAYLIST,
    CT_MEDIA_FILES,
    CT_PLAYING_MEDIA,
    CT_DETAILED_PLAYLIST,
    CT_METADATA,
    CT_HARDWARE
};

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

    MainMenuController* getMainMenuController() const;
    ScanfOptionController* getScanfOptionController() const;
    PlaylistController* getPlaylistController() const;
    MediaFileController* getMediaFileController() const;
    PlayingMediaController* getPlayingMediaController() const;
    DetailedPlaylistController* getDetailedPlaylistController() const;
    MetadataController* getMetadataController() const;
    ViewManager* getViewManager() const;
    ModelManager* getModelManager() const;
    //HardwareController* getHardwareController() const;
};

#endif // CONTROLLER_MANAGER_H
