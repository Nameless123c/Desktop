#pragma once
#include <afx.h>
#include <vector>
#include <string>

struct MediaItem {
    std::string id;
    std::string url;
    std::string fileName;

    MediaItem(); 
};

struct Message {
    std::string id;
    std::string content;
    std::vector<MediaItem> images;
    std::vector<MediaItem> files;
    int isSend;
    std::string createdAt;
    int messageType;

    Message(); 
};