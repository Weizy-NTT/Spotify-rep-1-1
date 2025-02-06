#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PlayingMediaController.hpp"
#include "ControllerManager.hpp"
#include "ViewManager.hpp"
#include "ModelManager.hpp"
#include "HardwareController.hpp"
#include "MediaFile.hpp"
#include "PlayingMedia.hpp"

// Mock classes
class MockPlayingMedia : public PlayingMedia {
public:
    MOCK_METHOD(void, setCurrentMediaFile, (const std::shared_ptr<MediaFile>& mediaFile), (override));
    MOCK_METHOD(void, adjustVolume, (size_t), (override));
    MOCK_METHOD(size_t, getTotalTime, (), (const, override));
    MOCK_METHOD(std::string, getDurationStringType, (), (const, override));
    MOCK_METHOD(void, setCurrentTime, (size_t), (override));
    MOCK_METHOD(int&, getVolume, (), (override));
    MOCK_METHOD(size_t&, getCurrentTime, (), (override));
    MOCK_METHOD(void, resumeMusic, (), (override));
    MOCK_METHOD(void, pauseMusic, (), (override));
    MOCK_METHOD(void, nextTrack, (), (override));
    MOCK_METHOD(void, previousTrack, (), (override));
};

class MockMediaFile : public MediaFile {
public:
    MOCK_METHOD(void, setName, (const std::string&), (override));
    MOCK_METHOD(void, setPath, (const std::string&), (override));
    MOCK_METHOD(void, setType, (MediaType), (override));
    MOCK_METHOD(void, setDuration, (const size_t& ), (override));
    MOCK_METHOD(void, setMetadata, (const Metadata&), (override));
};

class MockMediaFileLibrary : public MediaFileLibrary {
public:
    MOCK_METHOD(void, addMediaFile, (const std::shared_ptr<MediaFile>&), (override));
    MOCK_METHOD(std::shared_ptr<MediaFile>, getMediaFileByID, (const std::string&), (const, override));
    MOCK_METHOD(bool, isValidMediaFileNameInLibrary, (const std::string&), (override));
    MOCK_METHOD(bool, isValidMediaFileIDInLibrary, (const std::string&), (override));
};

class MockPlaylistLibrary : public PlaylistLibrary {
public:
    MOCK_METHOD(const std::vector<std::shared_ptr<Playlist>>&, getAllPlaylists, (), (const, override));
};

class MockPlayingMediaView : public PlayingMediaView {
public:
    MOCK_METHOD(void, showPlayingMedia, (PlayingMedia* player, size_t& currentTime, size_t totalTime, int& volume), (override));
    MOCK_METHOD(int, getSelectedOption, (), (const, override));
};

class MockScanfOptionView : public ScanfOptionView {
public:
    MOCK_METHOD(void, displayStatusMessage, (ScanStatus&), (override));
    MOCK_METHOD(int, getSelectedOption, (), (const, override));
};

class MockModelManager : public ModelManager {
public:
    MOCK_METHOD(MockPlayingMedia*, getPlayingMedia, (), (const, override));
    MOCK_METHOD(MockMediaFileLibrary*, getMediaLibrary, (), (const, override));
    MOCK_METHOD(MockPlaylistLibrary*, getPlaylistLibrary, (), (const, override));
};

class MockViewManager : public ViewManager {
public:
    MOCK_METHOD(void, hideCurrentView, (), (override));
    MOCK_METHOD(void, showCurrentView, (), (override));
    MOCK_METHOD(void, switchView, (SwitchView), (override));
    MOCK_METHOD(MockPlayingMediaView*, getPlayingMediaView, (), (const, override));
    MOCK_METHOD(MockScanfOptionView*, getScanfOptionView, (), (const, override));
};

class MockPlayingMediaController : public PlayingMediaController {
public:
    MOCK_METHOD(void, startUpdateThread, (), (override));
    MOCK_METHOD(void, stopUpdateThread, (), (override));
};

class MockHardwareController : public HardwareController {
public:
    MockHardwareController(const std::string& device, int baudRate)
        : HardwareController(device, baudRate) {}

    MOCK_METHOD(void, sendPlayCommand, (), (override));
    MOCK_METHOD(void, sendPauseCommand, (), (override));
    MOCK_METHOD(void, sendStopCommand, (), (override));
    MOCK_METHOD(void, sendSignal, (const std::string& signal), (override));
    MOCK_METHOD(void, startReading, (), (override));
    MOCK_METHOD(void, stopReading, (), (override));
};

class MockControllerManager : public ControllerManager {
public:
    MockControllerManager() : ControllerManager(nullptr, nullptr) {}

    MOCK_METHOD(ViewManager*, getViewManager, (), (const, override));
    MOCK_METHOD(ModelManager*, getModelManager, (), (const, override));
    MOCK_METHOD(MainMenuController*, getMainMenuController, (), (const, override));
    MOCK_METHOD(ScanfOptionController*, getScanfOptionController, (), (const, override));
    MOCK_METHOD(PlaylistController*, getPlaylistController, (), (const, override));
    MOCK_METHOD(MediaFileController*, getMediaFileController, (), (const, override));
    MOCK_METHOD(PlayingMediaController*, getPlayingMediaController, (), (const, override));
    MOCK_METHOD(DetailedPlaylistController*, getDetailedPlaylistController, (), (const, override));
    MOCK_METHOD(MetadataController*, getMetadataController, (), (const, override));
    MOCK_METHOD(HardwareController*, getHardwareController, (), (const, override));

    static void SetMockInstance(MockControllerManager* mockInstance) {
        instance = mockInstance;
    }
};