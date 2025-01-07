#ifndef SCANF_OPTION_VIEW_H
#define SCANF_OPTION_VIEW_H

#include "BaseView.hpp"

#define SCANF_DIRECTORY     "1"
#define SCANF_USB           "2"
#define BACK                "0"

class ScanfOptionView: public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    void handleInput(const std::string& input) override;
    ~ScanfOptionView() override = default;
};
#endif