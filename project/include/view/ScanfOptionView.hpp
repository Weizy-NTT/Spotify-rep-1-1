// #ifndef SCANF_OPTION_VIEW_H
// #define SCANF_OPTION_VIEW_H

// #include "BaseView.hpp"

// enum ScanfMenu {
//     BACK_FROM_SCAN,
//     SCANF_DIRECTORY,
//     SCANF_USB
// };

// enum ScanStatus {
//     SCAN_NORMAL,
//     SCAN_DIRECTORY_SUCCESS,
//     SCAN_DIRECTORY_FAILURE,
//     SCAN_USB_SUCCESS,
//     SCAN_USB_FAILURE,
// };

// class ScanfOptionView: public BaseView {
// public:
//     void showMenu() override;
//     void hideMenu() override;
//     ~ScanfOptionView() override = default;
//     void displayStatusMessage(ScanStatus& status);
// };
// #endif

#ifndef SCANF_OPTION_VIEW_H
#define SCANF_OPTION_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>

enum ScanStatus {
    SCAN_NORMAL,
    SCAN_DIRECTORY_SUCCESS,
    SCAN_DIRECTORY_FAILURE,
    SCAN_USB_SUCCESS,
    SCAN_USB_FAILURE,
};

enum ScanfMenu {
    SCANF_DIRECTORY,
    SCANF_USB,
    BACK_FROM_SCAN
};

class ScanfOptionView : public BaseView {
public:
    void showMenu() override;    // Hiển thị menu
    int getSelectedOption() const; // Lấy mục đã chọn
    ~ScanfOptionView() override = default;
    void hideMenu() override;
    void displayStatusMessage(ScanStatus& status);

private:
    int selected_option = 0;                     // Trạng thái lựa chọn
    std::vector<std::string> menu_entries = {    // Các mục trong menu
        "Scan Directory",
        "Scan USB Device",
        "Go Back"
    };
};

#endif // SCANF_OPTION_VIEW_H