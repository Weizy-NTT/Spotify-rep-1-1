#ifndef UART_HPP
#define UART_HPP

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <atomic>
#include <mutex>
#include <string>

/**
 * UART communication class
 */
class UART {
private:
    boost::asio::io_context io_context;       // IO context for Boost.Asio
    boost::asio::serial_port serial_port;     // Serial port object
    std::atomic<bool> running;                // Flag to check if the program is running
    std::mutex data_mutex;                    // Mutex to protect shared data
    std::string received_data;                // Data received from UART

public:
    UART(const std::string& port, unsigned int baud_rate); // Constructor
    ~UART();                                              // Destructor

    void writeData(const std::string& data);     // Send data via UART
    void readData();                            // Read data from UART
    void startReadLoop();                       // Start the read data loop
    void stop();                                // Stop UART communication
    
};

#endif // UART_HPP
