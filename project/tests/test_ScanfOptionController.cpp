#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ScanfOptionController.hpp"
#include "ControllerManager.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Mock classes
class MockViewManager : public ViewManager {
public:
    MOCK_METHOD(void, hideCurrentView, (), (override));
    MOCK_METHOD(void, switchView, (SwitchView), (override));
    MOCK_METHOD(std::shared_ptr<ScanfOptionView>, getScanfOptionView, (), (override));
};

class MockModelManager : public ModelManager {
public:
    MOCK_METHOD(std::shared_ptr<MediaLibrary>, getMediaLibrary, (), (override));
    MOCK_METHOD(std::shared_ptr<PlaylistLibrary>, getPlaylistLibrary, (), (override));
};

class MockMediaLibrary : public MediaFileLibrary {
public:
    MOCK_METHOD(bool, isValidMediaFileNameInLibrary, (const std::string&), (override));
    MOCK_METHOD(void, addMediaFile, (std::shared_ptr<MediaFile>), (override));
    MOCK_METHOD(std::shared_ptr<MediaFile>, getMediaFileByName, (const std::string&), (override));
};

class MockPlaylistLibrary : public PlaylistLibrary {
public:
    MOCK_METHOD(void, addPlaylist, (std::shared_ptr<Playlist>), (override));
    MOCK_METHOD(std::vector<std::shared_ptr<Playlist>>, getAllPlaylists, (), (override));
};

// Test fixture
class ScanfOptionControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up the mocks and controllers
        mockViewManager = std::make_shared<MockViewManager>();
        mockModelManager = std::make_shared<MockModelManager>();
        mockMediaLibrary = std::make_shared<MockMediaLibrary>();
        mockPlaylistLibrary = std::make_shared<MockPlaylistLibrary>();

        ON_CALL(*mockModelManager, getMediaLibrary()).WillByDefault(::testing::Return(mockMediaLibrary));
        ON_CALL(*mockModelManager, getPlaylistLibrary()).WillByDefault(::testing::Return(mockPlaylistLibrary));

        ControllerManager::getInstance()->setViewManager(mockViewManager);
        ControllerManager::getInstance()->setModelManager(mockModelManager);
    }

    std::shared_ptr<MockViewManager> mockViewManager;
    std::shared_ptr<MockModelManager> mockModelManager;
    std::shared_ptr<MockMediaLibrary> mockMediaLibrary;
    std::shared_ptr<MockPlaylistLibrary> mockPlaylistLibrary;
};

// Test scanDirectory
TEST_F(ScanfOptionControllerTest, ScanDirectory_AddsValidFilesToLibrary) {
    // Prepare test directory
    const std::string testDir = "test_scan_directory";
    fs::create_directory(testDir);
    std::ofstream(testDir + "/valid.mp3").close();
    std::ofstream(testDir + "/invalid.txt").close();

    EXPECT_CALL(*mockMediaLibrary, isValidMediaFileNameInLibrary("valid.mp3")).WillOnce(::testing::Return(false));
    EXPECT_CALL(*mockMediaLibrary, isValidMediaFileNameInLibrary("invalid.txt")).WillOnce(::testing::Return(false));
    EXPECT_CALL(*mockMediaLibrary, addMediaFile(::testing::_)).Times(1);

    ScanfOptionController controller;
    controller.scanDirectory(testDir);

    // Clean up
    fs::remove_all(testDir);
}

// Test scanUSB
TEST_F(ScanfOptionControllerTest, ScanUSB_ReturnsMountPoints) {
    // Prepare test USB directory
    const std::string testUSBDir = "/media/testuser";
    fs::create_directory(testUSBDir);
    fs::create_directory(testUSBDir + "/USB1");
    fs::create_directory(testUSBDir + "/USB2");

    setenv("USER", "testuser", 1);

    ScanfOptionController controller;
    std::vector<std::string> usbMountPoints = controller.scanUSB();

    EXPECT_EQ(usbMountPoints.size(), 2);
    EXPECT_NE(std::find(usbMountPoints.begin(), usbMountPoints.end(), testUSBDir + "/USB1"), usbMountPoints.end());
    EXPECT_NE(std::find(usbMountPoints.begin(), usbMountPoints.end(), testUSBDir + "/USB2"), usbMountPoints.end());

    // Clean up
    fs::remove_all("/media/testuser");
}

// Test scanPlaylistsFromTxt
TEST_F(ScanfOptionControllerTest, ScanPlaylistsFromTxt_AddsPlaylists) {
    // Prepare test playlist file
    const std::string playlistFile = "test_playlist.txt";
    std::ofstream outFile(playlistFile);
    outFile << "Playlist 1\n";
    outFile << "/path/to/song1.mp3\n";
    outFile << "/path/to/song2.mp3\n";
    outFile.close();

    EXPECT_CALL(*mockPlaylistLibrary, getAllPlaylists()).WillOnce(::testing::Return(std::vector<std::shared_ptr<Playlist>>{}));
    EXPECT_CALL(*mockPlaylistLibrary, addPlaylist(::testing::_)).Times(1);

    ScanfOptionController controller;
    controller.scanPlaylistsFromTxt(playlistFile);

    // Clean up
    fs::remove(playlistFile);
}
