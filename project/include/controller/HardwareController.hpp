#ifndef UART_CONTROLLER_HPP
#define UART_CONTROLLER_HPP

#include <string>
#include "UART.hpp" // Include the UART class you have implemented
#include "BaseController.hpp"

class HardwareController : public BaseController {
private:
    UART uart; // Use the UART class for communication

public:
    HardwareController(const std::string& device, int baudRate);
    void sendPlayCommand();    // Send a play command
    void sendPauseCommand();   // Send a pause command
    void sendStopCommand();    // Send a stop command
    void threadReading();      // Start a thread for reading data
    int getVolume();           // Get the current volume
    std::string receiveData(); // Receive data from the hardware
    void stopReading();        // Stop the reading thread
    void sendSignal(const std::string& signal); // Send a signal to the hardware
};


#endif // UART_CONTROLLER_HPP
