// #include "HardwareController.hpp"
// #include "ControllerManager.hpp"

// // Constructor: Khởi tạo HardwareController
// HardwareController::HardwareController(const std::string& device, int baudRate)
//     : uart(device, baudRate) {}

// // Gửi lệnh Play
// void HardwareController::sendPlayCommand() {
//     uart.writeData("PL");
// }

// // Gửi lệnh Pause
// void HardwareController::sendPauseCommand() {
//     uart.writeData("PA");
// }

// // Gửi lệnh Stop
// void HardwareController::sendStopCommand() {
//     uart.writeData("ST");
// }

// int HardwareController::getVolume() {
//     // Gửi lệnh yêu cầu volume
//     uart.writeData("VO");

//     // Chờ nhận phản hồi từ board (timeout là 1 giây)
//     std::string response;
//     for (int i = 0; i < 10; i++) { // 10 lần kiểm tra, mỗi lần 100ms
//         response = uart.readData();
//         if (!response.empty()) {
//             break; // Nếu nhận được dữ liệu thì thoát vòng lặp
//         }
//         usleep(100000); // Delay 100ms
//     }

//     // Nếu không nhận được phản hồi, trả về giá trị mặc định hoặc lỗi
//     if (response.empty()) {
//         std::cerr << "Error: No response from board." << std::endl;
//         return -1; // Giá trị lỗi
//     }

//     // Chuyển đổi response thành int
//     try {
//         return std::stoi(response);
//     } catch (const std::invalid_argument& e) {
//         std::cerr << "Error: Invalid response received: " << response << std::endl;
//         return -1; // Giá trị lỗi
//     } catch (const std::out_of_range& e) {
//         std::cerr << "Error: Response out of range: " << response << std::endl;
//         return -1; // Giá trị lỗi
//     }
// }

// // Nhận dữ liệu từ UART
// std::string HardwareController::receiveData() {
//     return uart.readData();
// }

// void HardwareController::threadReading(){
//     uart.startReadLoop();
// }

// void HardwareController::stopReading(){
//     uart.stop();
// }

// void HardwareController::sendSignal(const std::string& signal){
//     uart.writeData(signal);
// }