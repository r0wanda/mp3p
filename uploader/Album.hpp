#pragma once
#include <filesystem>

namespace fs = std::filesystem;

class Album;
class Song {
public:
    int idx;
    std::string name;
    fs::path path;
    Album album;
    Song() {};
};

class Album {
public:
    std::string artist;
    std::string name;
    fs::path cover;
    /**
     * dlmLen: length of delimeter
     * ex: "01: name"
     * change to 1 for "01 name"
     */
    Album(int dlmLen = 2): dlm(dlmLen) {
    }
private:
    int dlm;
};

class DB {

};