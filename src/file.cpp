#include "file_bridge.h"
#include <fstream>
#include <sstream>

// Writes content to a file (overwriting if it exists)
bool CPowerFileBridge::writeTextFile(const std::string& filepath, const std::string& content) {
    std::ofstream outFile(filepath);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << content;
    outFile.close();
    return true;
}

// Reads the entire contents of a text file into a string
std::string CPowerFileBridge::readTextFile(const std::string& filepath) {
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        return "";
    }
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    return buffer.str();
}

// Appends text to the end of an existing file
bool CPowerFileBridge::appendTextFile(const std::string& filepath, const std::string& content) {
    std::ofstream outFile(filepath, std::ios::app);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << content;
    outFile.close();
    return true;
}

// Deletes a file from the disk
bool CPowerFileBridge::deleteFile(const std::string& filepath) {
    return std::remove(filepath.c_str()) == 0;
}

// Checks if a file exists on the disk
bool CPowerFileBridge::fileExists(const std::string& filepath) {
    std::ifstream inFile(filepath);
    return inFile.good();
}
