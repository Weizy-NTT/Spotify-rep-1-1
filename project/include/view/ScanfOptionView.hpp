#ifndef SCANF_OPTION_VIEW_H
#define SCANF_OPTION_VIEW_H

#include "BaseView.hpp"

namespace ScanfMenu {
    const std::string SCANF_DIRECTORY = "1";
    const std::string SCANF_USB = "2";
    const std::string BACK = "0";
}

class ScanfOptionView: public BaseView {
public:
    void showMenu() override;
    void hideMenu() override;
    ~ScanfOptionView() override = default;
};
#endif