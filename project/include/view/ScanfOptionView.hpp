#ifndef SCANF_OPTION_VIEW_H
#define SCANF_OPTION_VIEW_H

#include "BaseView.hpp"

enum ScanfMenu {
    BACK_FROM_SCAN,
    SCANF_DIRECTORY,
    SCANF_USB
};

enum ScanStatus {
    SCAN_NORMAL,
    SCAN_DIRECTORY_SUCCESS,
    SCAN_DIRECTORY_FAILURE,
    SCAN_USB_SUCCESS,
    SCAN_USB_FAILURE,
};

class ScanfOptionView: public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    ~ScanfOptionView() override = default;
    void displayStatusMessage(ScanStatus& status);
};
#endif