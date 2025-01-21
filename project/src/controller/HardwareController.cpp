#include "HardwareController.hpp"
#include "ControllerManager.hpp"

// Constructor: Khởi tạo HardwareController
HardwareController::HardwareController(const std::string& device, int baudRate)
    : uart(device, baudRate) {}

// Gửi lệnh Play
void HardwareController::sendPlayCommand() {
    uart.writeData("PL");
}

// Gửi lệnh Pause
void HardwareController::sendPauseCommand() {
    uart.writeData("PA");
}

// Gửi lệnh Stop
void HardwareController::sendStopCommand() {
    uart.writeData("ST");
}


void HardwareController::threadReading(){
    uart.startReadLoop();
}

void HardwareController::stopReading(){
    uart.stop();
}

void HardwareController::sendSignal(const std::string& signal){
    uart.writeData(signal);
}