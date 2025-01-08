#include "ViewManager.hpp"
#include <iostream>

ViewManager::ViewManager() {
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


