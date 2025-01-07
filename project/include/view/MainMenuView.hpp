#ifndef MAIN_MENU_VIEW_H
#define MAIN_MENU_VIEW_H

#include "BaseView.hpp"

#define SCAN_OPTIONS    "1"
#define ALL_SONGS       "2"
#define PLAYLIST        "3"
#define EXIT            "0"

class MainMenuView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void handleInput(const std::string& input) override;
    ~MainMenuView() override = default;
};
#endif // MAIN_MENU_VIEW_H
