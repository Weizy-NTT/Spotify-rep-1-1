#include "ViewManager.hpp"
#include <iostream>

std::unique_ptr<ViewManager> ViewManager::instance = nullptr;

ViewManager::ViewManager() {
    currentView = std::make_unique<MainMenuView>();
}

void ViewManager::showCurrentView() {
    if (currentView) {
        currentView->showMenu();
    }
}

void ViewManager::switchView(std::unique_ptr<BaseView> newView) {
    currentView = std::move(newView);
    showCurrentView();
}

ViewManager& ViewManager::getInstance() {
    if (!instance) {
        instance = std::make_unique<ViewManager>();
    }
    return *instance;
}
