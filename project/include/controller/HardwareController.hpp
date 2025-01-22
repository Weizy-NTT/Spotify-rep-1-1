#ifndef UART_CONTROLLER_HPP
#define UART_CONTROLLER_HPP

#include <string>
#include <thread>
#include <atomic>
#include <functional>
#include "UART.hpp" // Include the UART class you have implemented
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
    UART uart; // UART giao tiếp phần cứng
    std::thread readThread; // Luồng đọc dữ liệu
    std::atomic<bool> running; // Trạng thái của luồng đọc

    // Xử lý dữ liệu từ UART
    void handleReceivedData(const std::string& data);

public:
    // Constructor
    HardwareController(const std::string& device, int baudRate);

    // Destructor
    ~HardwareController();

    // Gửi tín hiệu điều khiển
    void sendPlayCommand();
    void sendPauseCommand();
    void sendStopCommand();
    void sendSignal(const std::string& signal);

    // Bắt đầu và dừng luồng đọc dữ liệu
    void startReading();
    void stopReading();
};


#endif // UART_CONTROLLER_HPP
