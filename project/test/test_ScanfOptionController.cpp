#include <gtest/gtest.h>
#include <filesystem>
#include "ScanfOptionController.hpp"

namespace fs = std::filesystem;

class ScanfOptionControllerTest : public ::testing::Test {
protected:
    ScanfOptionController controller;
    std::string username = std::getenv("USER");  // Lấy user hiện tại
    std::string mediaPath = "/media/" + username;

    // Tạo thư mục giả lập trong thư mục /media/<current_user>/
    void SetUp() override {
        if (fs::exists(mediaPath)) {
            fs::remove_all(mediaPath);
        }

        // Tạo thư mục test cho user hiện tại
        fs::create_directory(mediaPath);

        // Tạo các thư mục giả lập đại diện cho USB
        fs::create_directory(mediaPath + "/usb1");
        fs::create_directory(mediaPath + "/usb2");
    }

    // Xóa các thư mục sau khi kiểm tra xong
    void TearDown() override {
        if (fs::exists(mediaPath)) {
            fs::remove_all(mediaPath);
        }
    }
};

// Kiểm tra trường hợp thư mục không tồn tại
TEST_F(ScanfOptionControllerTest, ScanUSB_NoMediaDirectory) {
    // Xóa thư mục /media/<current_user> nếu có
    fs::remove_all(mediaPath);

    // Kiểm tra scanUSB() khi không có thư mục người dùng
    std::vector<std::string> result = controller.scanUSB();

    EXPECT_TRUE(result.empty());  // Hàm trả về một vector rỗng
}

// Kiểm tra trường hợp thư mục không có USB
TEST_F(ScanfOptionControllerTest, ScanUSB_NoDirectory) {
    // Kiểm tra khi thư mục /media/<current_user> không có thư mục con
    fs::remove_all(mediaPath);
    fs::create_directory(mediaPath);

    // Kiểm tra scanUSB() khi thư mục không phải là thư mục USB
    std::vector<std::string> result = controller.scanUSB();

    EXPECT_TRUE(result.empty());  // Không có thư mục USB nào
}

// Kiểm tra khi có thư mục USB
TEST_F(ScanfOptionControllerTest, ScanUSB_WithMountPoints) {
    // Thư mục giả lập các thiết bị USB được mount
    std::vector<std::string> expected = {
        mediaPath + "/usb1",
        mediaPath + "/usb2"
    };

    // Kiểm tra scanUSB() với thư mục USB
    std::vector<std::string> result = controller.scanUSB();
    std::sort(result.begin(), result.end());  // Sắp xếp danh sách kết quả
    std::sort(expected.begin(), expected.end());  // Sắp xếp danh sách mong đợi

    EXPECT_EQ(result, expected);  // So sánh lại sau khi đã sắp xếp
}