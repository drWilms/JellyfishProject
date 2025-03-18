/**
 * @file SDManager.h
 * @brief Manages SD card operations, ensuring all paths start with '/'
 * @date 2025-03-16 09:25
 * @author Jan Wilms
 */

 #ifndef SDMANAGER_H
 #define SDMANAGER_H
 
 #include "FS.h"
 #include "SD.h"
 #include "SPI.h"
 
 class SDManager {
 public:
     static bool begin(uint8_t csPin);
     static void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
     static bool createFile(const char *path, const char *message);
     static bool appendFile(const char *path, const char *message);
     static bool renameFile(const char *oldPath, const char *newPath);
     static bool deleteFile(const char *path);
     static void ensureLeadingSlash(char *path);
     static bool isFileExists(fs::FS &fs, const char *fullName);


 };
 
 #endif // SDMANAGER_H
 