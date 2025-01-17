#ifndef UART_HPP
#define UART_HPP

#include "UART.hpp"
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <stdexcept>
#include <atomic>
#include <string>
#include <mutex>

extern std::mutex adc_mutex;  
extern std::mutex mode_mutex;  


class UART {
private:
    int uart_fd;               // File descriptor cho UART
    struct termios tty;        // Cấu hình UART
    bool running;  // Cờ để dừng chương trình

public:
    UART(const std::string& device, int baudRate);
    ~UART();

    bool isRunning() const;
    void writeData(const std::string& data);
    std::string readData();
    void startReadLoop();
    void stop();
};

#endif // UART_HPP
