#ifndef FILE_BRIDGE_H
#define FILE_BRIDGE_H

#include <string>

class CPowerFileBridge {
public:
    // File Operations
    static bool writeTextFile(const std::string& filepath, const std::string& content);
    static std::string readTextFile(const std::string& filepath);
    static bool appendTextFile(const std::string& filepath, const std::string& content);
    static bool deleteFile(const std::string& filepath);
    static bool fileExists(const std::string& filepath);
};

#endif // FILE_BRIDGE_H
