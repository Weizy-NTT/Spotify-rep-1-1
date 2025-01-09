#ifndef MAIN_MENU_VIEW_H
#define MAIN_MENU_VIEW_H

#include "BaseView.hpp"

enum MainMenu {
    EXIT,
    SCAN_OPTIONS,
    ALL_SONGS,
    PLAYLIST,
};

class MainMenuView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    ~MainMenuView() override = default;
};
#endif // MAIN_MENU_VIEW_H
