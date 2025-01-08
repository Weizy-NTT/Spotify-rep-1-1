#ifndef MEDIA_FILE_VIEW_H
#define MEDIA_FILE_VIEW_H

#include "BaseView.hpp"
#include "MediaFile.hpp"
#include <vector>

enum MediaFileMenu {
    BACK_FROM_MEDIA,
    PLAY_SONG,
    SHOW_DETAIL,
    NEXT_PAGE,
    PREV_PAGE
};

class MediaFileView : public BaseView {
public:
    void showMediaFilesPage(const std::vector<MediaFile>& files, int currentPage, int firstSong, int lastSong);
    void showMenu() override;
    void hideMenu() override;
    ~MediaFileView() override = default;
};
#endif // MEDIA_FILE_VIEW_H
