#include <gtest/gtest.h>
#include <filesystem>
#include "ScanfOptionController.hpp"

namespace fs = std::filesystem;

class ScanfOptionControllerTest : public ::testing::Test {
protected:
    ScanfOptionController controller;
    std::string username = "testuser";
    std::string mediaPath = "/media/" + username;

    // Tạo thư mục giả lập trong thư mục /media
    void SetUp() override {
        // Tạo thư mục test cho người dùng giả
        fs::create_directory(mediaPath);

        // Tạo các thư mục giả đại diện cho USB
        fs::create_directory(mediaPath + "/usb1");
        fs::create_directory(mediaPath + "/usb2");
    }

    // Xóa các thư mục sau khi kiểm tra xong
    void TearDown() override {
        fs::remove_all(mediaPath);  // Xóa tất cả các thư mục trong /media/testuser
    }
};

// Kiểm tra trường hợp thư mục không tồn tại
TEST_F(ScanfOptionControllerTest, ScanUSB_NoMediaDirectory) {
    // Xóa thư mục /media/testuser nếu có
    fs::remove_all(mediaPath);

    // Kiểm tra scanUSB() khi không có thư mục người dùng
    std::vector<std::string> result = controller.scanUSB();

    EXPECT_TRUE(result.empty());  // Hàm trả về một vector rỗng
}

// Kiểm tra trường hợp thư mục không phải là thư mục USB
TEST_F(ScanfOptionControllerTest, ScanUSB_NoDirectory) {
    // Kiểm tra khi thư mục /media/testuser không phải là thư mục con
    fs::remove_all(mediaPath);
    fs::create_directory(mediaPath);

    // Kiểm tra scanUSB() khi thư mục không phải là thư mục USB
    std::vector<std::string> result = controller.scanUSB();

    EXPECT_TRUE(result.empty());  // Không có thư mục USB nào
}

// Kiểm tra khi có thư mục USB
TEST_F(ScanfOptionControllerTest, ScanUSB_WithMountPoints) {
    // Thư mục /media/{username}/usb1 và usb2 giả lập
    std::vector<std::string> expected = {
        mediaPath + "/usb1",
        mediaPath + "/usb2"
    };

    // Kiểm tra scanUSB() với thư mục USB
    std::vector<std::string> result = controller.scanUSB();

    EXPECT_EQ(result.size(), 2);  // Nên có 2 thư mục USB
    EXPECT_EQ(result[0], expected[0]);
    EXPECT_EQ(result[1], expected[1]);
}

