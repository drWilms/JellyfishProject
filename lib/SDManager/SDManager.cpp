/**
 * @file SDManager.cpp
 * @brief Handles SD card operations, ensuring all paths start with '/'
 * @date 2025-03-16 09:25
 * @author Jan Wilms
 */

 #include "SDManager.h"

 
 bool SDManager::begin(uint8_t csPin) {
    static bool initialized = false;  // ✅ Prevent multiple mounts

    if (initialized) {
        Serial.println("[INFO] SD Card already initialized.");
        return true;
    }

    if (!SD.begin(csPin)) {
        Serial.println("[ERROR] SD Card Mount Failed!");
        return false;
    }

    Serial.println("SD Card Mounted!");
    initialized = true;  // ✅ Mark SD as initialized
    return true;
}

 void SDManager::listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
    if (dirname[0] != '/') {
        Serial.printf("[ERROR] Path must start with '/': %s\n", dirname);
        return;
    }

    Serial.printf("📂 Listing directory: %s\n", dirname);
    File root = fs.open(dirname);
    
    if (!root || !root.isDirectory()) {
        Serial.printf("[ERROR] Failed to open directory: %s\n", dirname);
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.printf("  DIR: %s\n", file.name());
            if (levels > 0) {
                // Ensure path correctness by removing redundant slashes
                String newPath = String(dirname);
                if (newPath != "/") newPath += "/";
                newPath += file.name();
                listDir(fs, newPath.c_str(), levels - 1);
            }
        } else {
            Serial.printf("  FILE: %s  SIZE: %d bytes\n", file.name(), file.size());
        }
        file = root.openNextFile();
    }
}

bool SDManager::isFileExists(fs::FS &fs, const char *fullName) {
    if (fullName[0] != '/') {
        Serial.printf("[ERROR] Path must start with '/': %s\n", fullName);
        return false;
    }

    File file = fs.open(fullName);
    if (!file || file.isDirectory()) {
        Serial.printf("[INFO] File not found: %s\n", fullName);
        return false;
    }

    file.close();
    Serial.printf("[INFO] File exists: %s\n", fullName);
    return true;
}



 
 bool SDManager::createFile(const char *path, const char *message) {
     char correctedPath[64];
     strncpy(correctedPath, path, sizeof(correctedPath) - 1);
     correctedPath[sizeof(correctedPath) - 1] = '\0';
     ensureLeadingSlash(correctedPath);
 
     Serial.printf("Creating file: %s\n", correctedPath);
     File file = SD.open(correctedPath, FILE_WRITE);
     if (!file) {
         Serial.printf("[ERROR] Failed to create file: %s\n", correctedPath);
         return false;
     }
     file.print(message);
     file.close();
     return true;
 }
 
 bool SDManager::appendFile(const char *path, const char *message) {
     char correctedPath[64];
     strncpy(correctedPath, path, sizeof(correctedPath) - 1);
     correctedPath[sizeof(correctedPath) - 1] = '\0';
     ensureLeadingSlash(correctedPath);
 
     Serial.printf("Appending to file: %s\n", correctedPath);
     File file = SD.open(correctedPath, FILE_APPEND);
     if (!file) {
         Serial.printf("[ERROR] Failed to open file for appending: %s\n", correctedPath);
         return false;
     }
     file.print(message);
     file.close();
     return true;
 }
 
 bool SDManager::renameFile(const char *oldPath, const char *newPath) {
     char correctedOldPath[64], correctedNewPath[64];
     strncpy(correctedOldPath, oldPath, sizeof(correctedOldPath) - 1);
     correctedOldPath[sizeof(correctedOldPath) - 1] = '\0';
     ensureLeadingSlash(correctedOldPath);
 
     strncpy(correctedNewPath, newPath, sizeof(correctedNewPath) - 1);
     correctedNewPath[sizeof(correctedNewPath) - 1] = '\0';
     ensureLeadingSlash(correctedNewPath);
 
     Serial.printf("Renaming %s to %s\n", correctedOldPath, correctedNewPath);
     if (!SD.rename(correctedOldPath, correctedNewPath)) {
         Serial.printf("[ERROR] Rename failed: %s -> %s\n", correctedOldPath, correctedNewPath);
         return false;
     }
     return true;
 }
 
 bool SDManager::deleteFile(const char *path) {
     char correctedPath[64];
     strncpy(correctedPath, path, sizeof(correctedPath) - 1);
     correctedPath[sizeof(correctedPath) - 1] = '\0';
     ensureLeadingSlash(correctedPath);
 
     Serial.printf("Deleting file: %s\n", correctedPath);
     if (!SD.remove(correctedPath)) {
         Serial.printf("[ERROR] Failed to delete file: %s\n", correctedPath);
         return false;
     }
     return true;
 }
 
 void SDManager::ensureLeadingSlash(char *path) {
     if (path[0] != '/') {
         memmove(path + 1, path, strlen(path) + 1);
         path[0] = '/';
     }
 }
 