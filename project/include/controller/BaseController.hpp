#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <string>

class BaseController {
public:
    virtual ~BaseController() = default; // Define a virtual destructor to ensure proper cleanup of derived classes
};

#endif // BASE_CONTROLLER_H

