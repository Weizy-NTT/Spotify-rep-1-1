#include "MediaFileView.hpp"
#include <iostream>

MediaFileView::MediaFileView() : currentPage(0) {}

int MediaFileView::calculateTotalPages(int totalFiles) {
    return (totalFiles + filesPerPage - 1) / filesPerPage;
}

void MediaFileView::showMediaFilesPage(const std::vector<MediaFile>& files, int page) {
    int totalFiles = files.size();
    int totalPages = calculateTotalPages(totalFiles);
    
    if (page < 0 || page >= totalPages) {
        std::cout << "Invalid page number." << std::endl;
        return;
    }

    int startIndex = page * filesPerPage;
    int endIndex = std::min(startIndex + filesPerPage, totalFiles);

    std::cout << "Showing page " << page + 1 << " of " << totalPages << std::endl;

    for (int i = startIndex; i < endIndex; ++i) {
        std::cout << "File " << i + 1 << ": " << files[i].getName() << std::endl;
    }

    std::cout << "\nEnter 'next' for next page, 'prev' for previous page, or 'back' to go back." << std::endl;
}

void MediaFileView::nextPage() {
    ++currentPage;
}

void MediaFileView::previousPage() {
    --currentPage;
}

void MediaFileView::showMenu() {
    std::cout << "\n--- Media Player Menu ---" << std::endl;
    std::cout << "1. Play\n";
    std::cout << "2. Show Media File Details\n";
    std::cout << "3. Show Next Page\n";
    std::cout << "4. Show Previous Page\n";
    std::cout << "0. Go Back\n";
    std::cout << "Please select an option: ";
}

void MediaFileView::hideMenu() {
    std::cout << "Hiding Media File View...\n";
}

void MediaFileView::handleInput(const std::string& input) {
    if (input == "1") {
        std::cout << "Play media file..." << std::endl;
    } else if (input == "2") {
        std::cout << "Showing media file details..." << std::endl;
    } else if (input == "3") {
        nextPage();
        std::cout << "Going to next page..." << std::endl;
    } else if (input == "4") {
        previousPage();
        std::cout << "Going to previous page..." << std::endl;
    } else if (input == "0") {
        std::cout << "Going back to the previous menu..." << std::endl;
    } else {
        std::cout << "Invalid input. Try again." << std::endl;
    }
}
