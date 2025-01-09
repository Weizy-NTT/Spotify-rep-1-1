#include "ViewManager.hpp"
#include "ModelManager.hpp"
#include "ControllerManager.hpp"
#include <iostream>
#include "ExceptionLib.hpp"

int main() {
    ControllerManager::getInstance(new ViewManager, new ModelManager)->getMainMenuController()->inputFromKeyboard();
    auto x = ControllerManager::getInstance()->getModelManager()->getMediaLibrary()->getAllMediaFiles();
    for (auto& i : x) {
        std::cout << i->getID() << ". " << i->getName() << std::endl;
    }
    return 0;
}
