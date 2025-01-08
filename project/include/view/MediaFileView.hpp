#ifndef MEDIA_FILE_VIEW_H
#define MEDIA_FILE_VIEW_H

#include "BaseView.hpp"
#include "MediaFile.hpp"
#include <vector>

namespace MediaFileMenu {
    const std::string PLAY = "1";
    const std::string SHOW_DETAIL = "2";
    const std::string NEXT_PAGE = "3";
    const std::string PREV_PAGE = "4";
    const std::string BACK = "0";
}

class MediaFileView : public BaseView {
public:
    void showMediaFilesPage(const std::vector<MediaFile>& files, int page);
    void showMenu() override;
    void hideMenu() override;
    ~MediaFileView() override = default;
};
#endif // MEDIA_FILE_VIEW_H
