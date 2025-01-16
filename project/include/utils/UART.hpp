#ifndef UART_HPP
#define UART_HPP

#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <atomic>

class UART {
private:
    int uart_fd;               // File descriptor cho UART
    struct termios tty;        // Cấu hình UART
    std::atomic<bool> running; // Cờ để dừng chương trình

public:
    UART(const std::string& device, int baudRate);
    ~UART();

    void writeData(const std::string& data);
    std::string readData();
    void startReadLoop();
    void stop();
};

#endif // UART_HPP
