#include "UART.hpp"
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <stdexcept>
#include "ControllerManager.hpp"
UART::UART(const std::string& device, int baudRate) : uart_fd(-1), running(true) {
    // Mở cổng UART
    uart_fd = open(device.c_str(), O_RDWR | O_NOCTTY);
    if (uart_fd < 0) {
        perror("Error opening UART");
        throw std::runtime_error("Failed to open UART");
    }

    // Cấu hình UART
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(uart_fd, &tty) != 0) {
        perror("Error from tcgetattr");
        throw std::runtime_error("Failed to get UART attributes");
    }

    // Cài đặt baud rate
    cfsetospeed(&tty, baudRate);
    cfsetispeed(&tty, baudRate);

    // 8N1: 8 data bits, no parity, 1 stop bit
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8-bit
    tty.c_cflag &= ~PARENB;                     // No parity
    tty.c_cflag &= ~CSTOPB;                     // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                    // No hardware flow control
    tty.c_cflag |= CREAD | CLOCAL;              // Enable read, disable modem control

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input mode
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // Disable software flow control
    tty.c_oflag &= ~OPOST;                         // Raw output mode

    // Cấu hình timeout
    tty.c_cc[VMIN] = 0;  // Không cần số byte tối thiểu
    tty.c_cc[VTIME] = 10; // Timeout sau 1 giây

    if (tcsetattr(uart_fd, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        throw std::runtime_error("Failed to set UART attributes");
    }
}

UART::~UART() {
    running = false;
    if (uart_fd >= 0) {
        close(uart_fd);
    }
}

void UART::writeData(const std::string& data) {
    int n = write(uart_fd, data.c_str(), data.size());
    if (n < 0) {
        perror("Error writing to UART");
    }
}

std::string UART::readData() {
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    int n = read(uart_fd, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        perror("Error reading from UART");
        return "";
    }
    return std::string(buffer, n);
}

void UART::startReadLoop() {
        std::thread([this]() {
            while (running) {
                std::string data = readData();
                if (data == "1"){
                    ControllerManager::getInstance()->getPlayingMediaController()->skipToNext();
                }
                if(data == "3"){
                    ControllerManager::getInstance()->getPlayingMediaController()->play();
                }
                if(data == "6"){
                    ControllerManager::getInstance()->getPlayingMediaController()->pause();
                }
                if (data == "4"){
                    ControllerManager::getInstance()->getPlayingMediaController()->skipToPrevious();
                }
                if (!data.empty()) {
                    std::cout << "Received: " << data << std::endl;
                }
            }
        }).detach();
    }
void UART::stop() {
    running = false;
}
