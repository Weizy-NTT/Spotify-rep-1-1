// #include "UART.hpp"
// #include <iostream>
// #include <fcntl.h>
// #include <termios.h>
// #include <unistd.h>
// #include <cstring>
// #include <thread>
// #include <stdexcept>
// #include <atomic>
// #include <string>
// #include <mutex>
// #include "ControllerManager.hpp"


// std::mutex adc_mutex;       // Mutex bảo vệ adcValue
// std::mutex mode_mutex;      // Mutex bảo vệ mode        // Biến cho giá trị ADC

// UART::UART(const std::string& device, int baudRate) : uart_fd(-1), running(true) {
//     uart_fd = open(device.c_str(), O_RDWR | O_NOCTTY);
//     if (uart_fd < 0) {
//         perror("Error opening UART");
//         throw std::runtime_error("Failed to open UART");
//     }

//     memset(&tty, 0, sizeof(tty));
//     if (tcgetattr(uart_fd, &tty) != 0) {
//         perror("Error from tcgetattr");
//         throw std::runtime_error("Failed to get UART attributes");
//     }

//     cfsetospeed(&tty, baudRate);
//     cfsetispeed(&tty, baudRate);

//     tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
//     tty.c_cflag &= ~PARENB;
//     tty.c_cflag &= ~CSTOPB;
//     tty.c_cflag &= ~CRTSCTS;
//     tty.c_cflag |= CREAD | CLOCAL;

//     tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
//     tty.c_iflag &= ~(IXON | IXOFF | IXANY);
//     tty.c_oflag &= ~OPOST;

//     tty.c_cc[VMIN] = 0;  // Không cần số byte tối thiểu
//     tty.c_cc[VTIME] = 10; // Timeout sau 1 giây

//     if (tcsetattr(uart_fd, TCSANOW, &tty) != 0) {
//         perror("Error from tcsetattr");
//         throw std::runtime_error("Failed to set UART attributes");
//     }

//     running = true;
// }

// UART::~UART() {
//     running = false;
//     if (uart_fd >= 0) {
//         close(uart_fd);
//     }
// }

// std::string UART::readData() {
//     char buffer[256];
//     memset(buffer, 0, sizeof(buffer));
//     int n = read(uart_fd, buffer, sizeof(buffer) - 1);
//     if (n < 0) {
//         perror("Error reading from UART");
//         return "";
//     }
//     return std::string(buffer, n);
// }

// void UART::startReadLoop() {
//     std::thread([this]() {
//         std::string receivedData = "";
//         while (running) {
//             std::string data = readData();  // Đọc dữ liệu từ UART
//             if (!data.empty()) {
//                 // Nếu là ký tự A, B, C, D thì xử lý ngay
//                 if (data == "A" || data == "B" || data == "C" || data == "D") 
//                 {
//                     if(data == "C"){
//                         ControllerManager::getInstance()->getPlayingMediaController()->play();
//                     }
//                     else if(data =="D"){
//                         ControllerManager::getInstance()->getPlayingMediaController()->pause();
//                     }else if(data == "A"){
//                         ControllerManager::getInstance()->getPlayingMediaController()->skipToNext();
//                     }else if(data =="B"){
//                         ControllerManager::getInstance()->getPlayingMediaController()->skipToPrevious();
//                     }
//                 }
//                 // Nếu là số, lưu vào buffer
//                 else {
//                     receivedData += data;

//                     // Nếu nhận đủ 4 ký tự thì chuyển thành số
//                     if (receivedData.length() == 4) {
//                         std::lock_guard<std::mutex> lock(adc_mutex);
//                         try {
//                             ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setVolume(std::stoi(receivedData));
//                         } catch (const std::invalid_argument& e) {
//                             std::cerr << "Invalid ADC value: " << receivedData << std::endl;
//                         }
//                         // Reset lại buffer sau khi xử lý
//                         receivedData = "";
//                     }
//                 }
//             }
//         }
//     }).detach();  // Detach thread để không cần join
// }

// void UART::stop() {
//     running = false;
// }

// void UART::writeData(const std::string& data) {
//     write(uart_fd, data.c_str(), data.size());
// }

#include "ControllerManager.hpp"
#include "UART.hpp"
#include <iostream>
#include <thread>
#include <boost/system/system_error.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>

// Constructor
UART::UART(const std::string& port, unsigned int baud_rate)
    : serial_port(io_context), running(true) {
    try {
        // Mở cổng serial
        serial_port.open(port);

        // Cấu hình cổng serial
        serial_port.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
        serial_port.set_option(boost::asio::serial_port_base::character_size(8));
        serial_port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        serial_port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
        serial_port.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

        std::cout << "Serial port opened successfully on " << port << " with baud rate " << baud_rate << ".\n";
    } catch (const boost::system::system_error& e) {
        std::cerr << "Error opening serial port: " << e.what() << std::endl;
        throw;
    }
}

// Destructor
UART::~UART() {
    stop();
}

// Gửi dữ liệu qua UART
void UART::writeData(const std::string& data) {
    try {
        boost::asio::write(serial_port, boost::asio::buffer(data));
        //std::cout << "Data sent: " << data << std::endl;
    } catch (const boost::system::system_error& e) {
        //std::cerr << "Error sending data: " << e.what() << std::endl;
    }
}

// Đọc dữ liệu từ UART
void UART::readData() {
    try {
        char buffer[256];
        std::string receivedData;
        while (running) {
            size_t bytes_read = serial_port.read_some(boost::asio::buffer(buffer));
            if (bytes_read > 0) {
                std::lock_guard<std::mutex> lock(data_mutex);

                // Thêm dữ liệu mới vào buffer
                receivedData.append(buffer, bytes_read);

                // Tách dữ liệu theo dấu '\n'
                size_t pos;
                while ((pos = receivedData.find('\n')) != std::string::npos) {
                    std::string data = receivedData.substr(0, pos); // Lấy giá trị trước '\n'
                    receivedData.erase(0, pos + 1); // Xóa phần đã xử lý

                    if (!data.empty()) {
                        // Nếu là ký tự đơn (A, B, C, D)
                        if (data.length() == 1 && (data == "A" || data == "B" || data == "C" || data == "D")) {
                            if (data == "C") {
                                ControllerManager::getInstance()->getPlayingMediaController()->play();
                            } else if (data == "D") {
                                ControllerManager::getInstance()->getPlayingMediaController()->pause();
                            } else if (data == "A") {
                                ControllerManager::getInstance()->getPlayingMediaController()->skipToNext();
                            } else if (data == "B") {
                                ControllerManager::getInstance()->getPlayingMediaController()->skipToPrevious();
                            }
                        }
                        // Nếu là chuỗi số
                        else if (std::all_of(data.begin(), data.end(), ::isdigit)) {
                            ControllerManager::getInstance()->getModelManager()->getPlayingMedia()->setVolume(std::stoi(data));
                            //std::cout << "Volume set to: " << volume << std::endl;
                        }
                        // Xử lý dữ liệu không mong muốn
                        else {
                            std::cout << "Unhandled data: " << data << std::endl;
                        }
                    }
                }
            }
        }
    } catch (const boost::system::system_error& e) {
        if (running) {
            std::cerr << "Error reading data: " << e.what() << std::endl;
        }
    }
}

// Bắt đầu vòng lặp đọc dữ liệu
void UART::startReadLoop() {
    std::thread([this]() {
        readData();
    }).detach();
}

// Dừng giao tiếp UART
void UART::stop() {
    running = false;
    if (serial_port.is_open()) {
        serial_port.close();
    }
    std::cout << "Serial communication stopped.\n";
}
