#ifndef MAIN_MENU_VIEW_H
#define MAIN_MENU_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>

enum MainMenu {
    SCAN_OPTIONS,
    ALL_SONGS,
    PLAYLIST,
    NOW_PLAYING,
    EXIT
};

class MainMenuView : public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    int getSelectedOption() const; // Thêm hàm getter để lấy option được chọn
    ~MainMenuView() override = default;

private:
    int selected_option = 0;                     // Biến lưu trữ lựa chọn
    std::vector<std::string> menu_entries = {    // Danh sách các mục trong menu
        "Scan Options",
        "All Songs",
        "Playlist",
        "Now Playing",
        "Exit"
    };
};

#endif // MAIN_MENU_VIEW_H
