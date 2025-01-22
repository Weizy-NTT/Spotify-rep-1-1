#ifndef UART_CONTROLLER_HPP
#define UART_CONTROLLER_HPP

#include <string>
#include <thread>
#include <atomic>
#include <functional>
#include "UART.hpp" 
#include "BaseController.hpp"

#define PLAY_MODE_RECEIVE       "C"
#define PAUSE_MODE_RECEIVE      "D"
#define NEXT_MODE_RECEIVE       "A"
#define PREV_MODE_RECEIVE       "B"

#define PAUSE_MODE      "PA"
#define PLAY_MODE       "PL"
#define STOP_MODE       "ST"


class HardwareController : public BaseController {
private:
    UART uart;
    std::thread readThread; 
    std::atomic<bool> running; 

    void handleReceivedData(const std::string& data);

public:
    HardwareController(const std::string& device, int baudRate);

    ~HardwareController();

    void sendPlayCommand();

    void sendPauseCommand();

    void sendStopCommand();

    void sendSignal(const std::string& signal);

    void startReading();

    void stopReading();
};


#endif // UART_CONTROLLER_HPP
