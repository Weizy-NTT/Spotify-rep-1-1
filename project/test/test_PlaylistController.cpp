// #include <gtest/gtest.h>
// #include <gmock/gmock.h>
// #include "PlaylistController.hpp"
// #include "ControllerManager.hpp"
// #include "ModelManager.hpp"
// #include "ViewManager.hpp"
// #include "PlaylistLibrary.hpp"
// #include "PlaylistView.hpp"
// #include "Playlist.hpp"

// // Mock classes for dependencies
// class MockViewManager : public ViewManager {
// public:
//     // Mock the methods you need in your test
//     MOCK_METHOD(void, showCurrentView, (), (override));
//     MOCK_METHOD(void, hideCurrentView, (), (override));
//     MOCK_METHOD(void, switchView, (SwitchView viewIndex), (override));

//     MOCK_METHOD(ScanfOptionView*, getScanfOptionView, (), (const, override));
//     MOCK_METHOD(PlaylistView*, getPlaylistView, (), (const, override));
//     MOCK_METHOD(MediaFileView*, getMediaFileView, (), (const, override));
//     MOCK_METHOD(PlayingMediaView*, getPlayingMediaView, (), (const, override));
//     MOCK_METHOD(DetailedPlaylistView*, getDetailedPlaylistView, (), (const, override));
//     MOCK_METHOD(MetadataView*, getMetadataView, (), (const, override));
//     MOCK_METHOD(MainMenuView*, getMainMenuView, (), (const, override));
//     ~MockViewManager() override = default;
// };

// class MockModelManager : public ModelManager {
// public:
//     MOCK_METHOD(MediaFileLibrary*, getMediaLibrary, (), (const, override));
//     MOCK_METHOD(PlaylistLibrary*, getPlaylistLibrary, (), (const, override));
//     MOCK_METHOD(PlayingMedia*, getPlayingMedia, (), (const, override));
//     ~MockModelManager() override = default;
// };

// // Mock ControllerManager class
// class MockControllerManager : public ControllerManager {
// public:
//     MockControllerManager(ViewManager* viewManager, ModelManager* modelManager)
//         : ControllerManager(viewManager, modelManager) {}

//     // Mocking static getInstance method
//     static MockControllerManager* getMockInstance(ViewManager* viewManager, ModelManager* modelManager) {
//         if (instance == nullptr) {
//             instance = new MockControllerManager(viewManager, modelManager);
//         }
//         return static_cast<MockControllerManager*>(instance);
//     }

//     // Mocking getters for each controller
//     MOCK_METHOD(MainMenuController*, getMainMenuController, (), (const, override));
//     MOCK_METHOD(ScanfOptionController*, getScanfOptionController, (), (const, override));
//     MOCK_METHOD(PlaylistController*, getPlaylistController, (), (const, override));
//     MOCK_METHOD(MediaFileController*, getMediaFileController, (), (const, override));
//     MOCK_METHOD(PlayingMediaController*, getPlayingMediaController, (), (const, override));
//     MOCK_METHOD(DetailedPlaylistController*, getDetailedPlaylistController, (), (const, override));
//     MOCK_METHOD(MetadataController*, getMetadataController, (), (const, override));
//     MOCK_METHOD(HardwareController*, getHardwareController, (), (const, override));
    
//     // Mocking the ViewManager and ModelManager getter
//     MOCK_METHOD(ViewManager*, getViewManager, (), (const, override));
//     MOCK_METHOD(ModelManager*, getModelManager, (), (const, override));
//     ~MockControllerManager() override = default;
// };

// class MockPlaylistLibrary : public PlaylistLibrary {
// public:
//     MOCK_METHOD(void, addPlaylist, (const std::shared_ptr<Playlist>& playlist), (override));
//     MOCK_METHOD(void, removePlaylist, (const std::string& id), (override));
//     MOCK_METHOD(bool, isValidPlaylistIDInLibrary, (const std::string& id), (override));
//     MOCK_METHOD(const std::vector<std::shared_ptr<Playlist>>&, getAllPlaylists, (), (const, override));
//     ~MockPlaylistLibrary() override = default;
// };

// class MockPlaylistView : public PlaylistView {
// public:
//     MOCK_METHOD(void, showMenu, (), (override));
//     MOCK_METHOD(int, getSelectedOption, (), (const, override));
//     MOCK_METHOD(void, hideMenu, (), (override));
//     MOCK_METHOD(void, showPlaylistList, (const std::vector<std::shared_ptr<Playlist>>&), (override));
//     MOCK_METHOD(void, displayStatusMessage, (PlaylistStatus&), (override));
//     ~MockPlaylistView() override = default;
// };

// class PlaylistControllerTest : public ::testing::Test {
// protected:
//     std::shared_ptr<MockViewManager> mockViewManager;
//     std::shared_ptr<MockModelManager> mockModelManager;
//     std::shared_ptr<MockPlaylistLibrary> mockPlaylistLibrary;
//     std::shared_ptr<MockPlaylistView> mockPlaylistView;
//     std::shared_ptr<MockControllerManager> mockControllerManager;
//     PlaylistController* controller;  // changed from `controller` to pointer

//     void SetUp() override {
//         mockViewManager = std::make_shared<MockViewManager>();
//         mockModelManager = std::make_shared<MockModelManager>();
//         mockPlaylistLibrary = std::make_shared<MockPlaylistLibrary>();
//         mockPlaylistView = std::make_shared<MockPlaylistView>();

//         // Create a mock ControllerManager instance
//         mockControllerManager = std::make_shared<MockControllerManager>(mockViewManager.get(), mockModelManager.get());

//         // Now initialize PlaylistController with the mock ControllerManager
//         controller = new PlaylistController();  // No longer directly instantiated without dependency injection
        
//         // Set up the mock methods to return the mocks we created
//         EXPECT_CALL(*mockModelManager, getPlaylistLibrary()).WillRepeatedly(testing::Return(mockPlaylistLibrary.get()));
//         EXPECT_CALL(*mockViewManager, getPlaylistView()).WillRepeatedly(testing::Return(mockPlaylistView.get()));
//     }

//     void TearDown() override {
//         delete controller;  // Clean up the dynamically allocated controller
//     }
// };

// // Test creating a playlist
// TEST_F(PlaylistControllerTest, CreatePlaylist_AddsToLibrary) {
//     std::string playlistName = "My Playlist";

//     // Expect addPlaylist to be called with a playlist
//     EXPECT_CALL(*mockPlaylistLibrary, addPlaylist(testing::_)).Times(1);

//     controller->createPlaylist(playlistName);
// }

// // Test deleting a playlist
// TEST_F(PlaylistControllerTest, DeletePlaylist_RemovesFromLibrary) {
//     std::string playlistID = "123";

//     // Expect removePlaylist to be called with the correct playlist ID
//     EXPECT_CALL(*mockPlaylistLibrary, removePlaylist(playlistID)).Times(1);

//     controller->deletePlaylist(playlistID);
// }

// // Test displaying all playlists
// TEST_F(PlaylistControllerTest, ShowAllPlaylists_DisplaysCorrectly) {
//     std::vector<std::shared_ptr<Playlist>> playlists = {
//         std::make_shared<Playlist>("Playlist 1"),
//         std::make_shared<Playlist>("Playlist 2")
//     };

//     // Expect showPlaylistList to be called with the correct playlists
//     EXPECT_CALL(*mockPlaylistView, showPlaylistList(playlists)).Times(1);

//     controller->showAllPlaylists(playlists);
// }

// // Test handling user input for selecting a playlist
// TEST_F(PlaylistControllerTest, HandleInput_SelectPlaylist) {
//     std::string playlistID = "123";

//     // Mock user input to select the playlist menu option
//     EXPECT_CALL(*mockPlaylistView, getSelectedOption()).WillOnce(testing::Return(PlaylistMenu::SELECT_PLAYLIST));
//     EXPECT_CALL(*mockPlaylistLibrary, isValidPlaylistIDInLibrary(playlistID)).WillOnce(testing::Return(true));

//     // Expect the DetailedPlaylistController to be called
//     EXPECT_CALL(*mockControllerManager, getDetailedPlaylistController()).Times(1);

//     controller->handleInput();
// }

// // Test handling user input for adding a playlist
// TEST_F(PlaylistControllerTest, HandleInput_AddPlaylist) {
//     std::string playlistName = "New Playlist";

//     // Mock user input for adding a playlist
//     EXPECT_CALL(*mockPlaylistView, getSelectedOption()).WillOnce(testing::Return(PlaylistMenu::ADD_PLAYLIST));
//     EXPECT_CALL(*mockPlaylistLibrary, addPlaylist(testing::_)).Times(1);

//     controller->handleInput();
// }

// // Test handling user input for removing a playlist
// TEST_F(PlaylistControllerTest, HandleInput_RemovePlaylist) {
//     std::string playlistID = "123";

//     // Mock user input for removing a playlist
//     EXPECT_CALL(*mockPlaylistView, getSelectedOption()).WillOnce(testing::Return(PlaylistMenu::REMOVE_PLAYLIST));
//     EXPECT_CALL(*mockPlaylistLibrary, isValidPlaylistIDInLibrary(playlistID)).WillOnce(testing::Return(true));
//     EXPECT_CALL(*mockPlaylistLibrary, removePlaylist(playlistID)).Times(1);

//     controller->handleInput();
// }

// // Test handling the back navigation option
// TEST_F(PlaylistControllerTest, HandleInput_Back) {
//     // Mock user input for back option
//     EXPECT_CALL(*mockPlaylistView, getSelectedOption()).WillOnce(testing::Return(PlaylistMenu::BACK_FROM_PLAYLIST));

//     controller->handleInput();
// }
