#ifndef BASE_VIEW_H
#define BASE_VIEW_H

#include <string>

class BaseView {
protected:
    bool statusView; // Indicates whether the view is currently shown or hidden

public:
    // Constructor to initialize the base view
    BaseView();

    // Display the menu
    virtual void showMenu();

    // Hide the menu
    virtual void hideMenu();

    // Check if the menu is currently shown
    bool isShown() const;

    // Virtual destructor to allow proper cleanup of derived classes
    virtual ~BaseView();
};

#endif // BASE_VIEW_H