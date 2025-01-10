#include "ViewManager.hpp"
#include "ModelManager.hpp"
#include "ControllerManager.hpp"
#include <iostream>
#include "ExceptionLib.hpp"

int main() {
    ControllerManager::getInstance(new ViewManager, new ModelManager)->getMainMenuController()->handleInput();
    return 0;
}
