#ifndef MAIN_MENU_VIEW_H
#define MAIN_MENU_VIEW_H

#include "BaseView.hpp"

namespace MainMenu {
    const std::string SCAN_OPTIONS = "1";
    const std::string ALL_SONGS = "2";
    const std::string PLAYLIST = "3";
    const std::string EXIT = "0";
}

class MainMenuView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    ~MainMenuView() override = default;
};
#endif // MAIN_MENU_VIEW_H
