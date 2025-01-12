#ifndef MEDIA_FILE_VIEW_H
#define MEDIA_FILE_VIEW_H

#include "BaseView.hpp"
#include "MediaFile.hpp"
#include <vector>
#include <memory>

enum MediaFileMenu {
    BACK_FROM_MEDIA,
    PLAY_SONG_FROM_FILES,
    SHOW_DETAIL,
    NEXT_PAGE,
    PREV_PAGE
};

enum MediaFileStatus {
    MEDIAFILE_NORMAL,
    MEDIAFILE_PLAY_STATUS,
    MEDIAFILE_DETAIL_STATUS,
    MEDIAFILE_NEXT_PAGE_STATUS,
    MEDIAFILE_PREV_PAGE_STATUS,
};

class MediaFileView : public BaseView {
public:
    void showMediaFilesPage(const std::vector<std::shared_ptr<MediaFile>>& files, size_t currentPage, size_t firstSong, size_t lastSong);
    void showMenu() override;
    void hideMenu() override;
    ~MediaFileView() override = default;
    void displayStatusMessage(MediaFileStatus& status);
};
#endif // MEDIA_FILE_VIEW_H
