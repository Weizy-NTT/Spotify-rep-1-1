#ifndef UART_HPP
#define UART_HPP


#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <atomic>
#include <mutex>
#include <string>




class UART {
private:
    boost::asio::io_context io_context;       // IO context cho Boost.Asio
    boost::asio::serial_port serial_port;     // Serial port object
    std::atomic<bool> running;                // Cờ kiểm tra chương trình có đang chạy không
    std::mutex data_mutex;                    // Mutex bảo vệ dữ liệu
    std::string received_data;                // Dữ liệu nhận từ UART

public:
    UART(const std::string& port, unsigned int baud_rate);
    ~UART();

    void writeData(const std::string& data);     // Gửi dữ liệu qua UART
    void readData();                            // Đọc dữ liệu từ UART
    void startReadLoop();                       // Bắt đầu vòng lặp đọc dữ liệu
    void stop();                                // Dừng giao tiếp UART
    
};

#endif // UART_HPP
