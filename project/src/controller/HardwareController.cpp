#include "HardwareController.hpp"
#include "ControllerManager.hpp"

// Constructor: Initialize the HardwareController
// Sets up a UART connection using the specified device and baud rate.
HardwareController::HardwareController(const std::string& device, int baudRate)
    : uart(device, baudRate) {}

// Send the "Play" command
// Sends a "PL" signal through the UART connection to trigger the Play action on the hardware.
void HardwareController::sendPlayCommand() {
    uart.writeData(PLAY_MODE);
}

// Send the "Pause" command
// Sends a "PA" signal through the UART connection to trigger the Pause action on the hardware.
void HardwareController::sendPauseCommand() {
    uart.writeData(PAUSE_MODE);
}

// Send the "Stop" command
// Sends a "ST" signal through the UART connection to trigger the Stop action on the hardware.
void HardwareController::sendStopCommand() {
    uart.writeData(STOP_MODE);
}

// Start reading data in a separate thread
// Begins the UART data reading loop, allowing the controller to continuously read incoming data.
void HardwareController::threadReading() {
    uart.startReadLoop();
}

// Stop reading data
// Stops the UART data reading loop, halting any ongoing reading operations.
void HardwareController::stopReading() {
    uart.stop();
}

// Send a custom signal
// Sends a custom string signal through the UART connection for hardware-specific actions.
void HardwareController::sendSignal(const std::string& signal) {
    uart.writeData(signal);
}
