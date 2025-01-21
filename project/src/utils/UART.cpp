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

        //std::cout << "Serial port opened successfully on " << port << " with baud rate " << baud_rate << ".\n";
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
