#ifndef SCANF_OPTION_VIEW_H
#define SCANF_OPTION_VIEW_H

#include "BaseView.hpp"

enum ScanfMenu {
    BACK_FROM_SCAN,
    SCANF_DIRECTORY,
    SCANF_USB
};

class ScanfOptionView: public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    ~ScanfOptionView() override = default;
};
#endif