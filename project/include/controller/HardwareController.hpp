#ifndef UART_CONTROLLER_HPP
#define UART_CONTROLLER_HPP

#include <string>
#include "UART.hpp" // Include lớp UART bạn đã viết
#include "ControllerManager.hpp"

class HardwareController : public BaseController {
private:
    UART uart; // Sử dụng lớp UART để giao tiếp

public:
    HardwareController(const std::string& device, int baudRate);
    void sendPlayCommand();
    void sendPauseCommand();
    void sendStopCommand();
    void threadReading();
    int getVolume();
    std::string receiveData();
    void stopReading()
};

#endif // UART_CONTROLLER_HPP
