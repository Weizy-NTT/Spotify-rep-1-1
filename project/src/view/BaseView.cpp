#include "BaseView.hpp"

BaseView::BaseView():statusView(false) {}

void BaseView::showMenu() {
    statusView = true;
}

void BaseView::hideMenu() {
    statusView = false;
}

bool BaseView::isShown() const {
    return statusView;
}

BaseView::~BaseView() {}