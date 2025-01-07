#ifndef MEDIA_FILE_VIEW_H
#define MEDIA_FILE_VIEW_H

#include "BaseView.hpp"
#include "MediaFile.hpp"
#include <vector>

class MediaFileView : public BaseView {
private:
    int currentPage;
    const int filesPerPage = 25;
    
    int calculateTotalPages(int totalFiles);
public:
    MediaFileView();

    void showMediaFilesPage(const std::vector<MediaFile>& files, int page);

    void nextPage();

    void previousPage();

    void showMenu() override;

    void hideMenu() override;

    void handleInput(const std::string& input) override;
};

#endif // MEDIA_FILE_VIEW_H
