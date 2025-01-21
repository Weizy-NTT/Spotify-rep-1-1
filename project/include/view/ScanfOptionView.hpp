#ifndef SCANF_OPTION_VIEW_H
#define SCANF_OPTION_VIEW_H

#include "BaseView.hpp"
#include <vector>
#include <string>

// Enum for scan statuses
enum ScanStatus {
    SCAN_NORMAL,              // Normal scan status
    SCAN_DIRECTORY_SUCCESS,   // Status indicating directory scan was successful
    SCAN_DIRECTORY_FAILURE,   // Status indicating directory scan failed
    SCAN_USB_SUCCESS,         // Status indicating USB scan was successful
    SCAN_USB_FAILURE          // Status indicating USB scan failed
};

// Enum for scan menu options
enum ScanfMenu {
    SCANF_DIRECTORY,          // Option to scan a directory
    SCANF_USB,                // Option to scan a USB device
    BACK_FROM_SCAN            // Option to go back to the previous menu
};

class ScanfOptionView : public BaseView {
public:
    // Override to display the menu
    void showMenu() override;

    // Getter to retrieve the user's selected option
    int getSelectedOption() const;

    // Destructor
    ~ScanfOptionView() override = default;

    // Override to hide the menu
    void hideMenu() override;

    // Display a status message based on the current scan status
    void displayStatusMessage(ScanStatus& status);

private:
    int selected_option = 0;                     // Variable to store the user's selected option
    std::vector<std::string> menu_entries = {    // List of menu entries
        "Scan Directory",
        "Scan USB Device",
        "Go Back"
    };
};

#endif // SCANF_OPTION_VIEW_H