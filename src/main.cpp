/**
 * @file main.cpp
 * @brief Jellyfish Project - Main Program
 * @author Jan Wilms
 * @date 2025-03-16 17:25 (Amsterdam Time)
 */

 #include <Arduino.h>
 #include "freertos/FreeRTOS.h"
 #include "freertos/task.h"
 #include "AudioManager.h"
 #include "LightManager.h"
 #include "TimeManager.h"
 #include "SDManager.h"
 #include "HWconfig.h"
 
 TaskHandle_t Task1_Handle = NULL;
 TaskHandle_t Task2_Handle = NULL;
 TaskHandle_t Task3_Handle = NULL;
 TaskHandle_t Task4_Handle = NULL;
 TaskHandle_t Task5_Handle = NULL;
 TaskHandle_t Task6_Handle = NULL;  // NEW: Task for playing fragments
 
 LightManager lightManager;
 AudioManager audioManager(SD_CS, PIN_I2S_BCLK, PIN_I2S_LRC, PIN_I2S_DOUT, &lightManager);
 TimeManager timeManager;
 SDManager sdManager; 
 
 PlaylistEntry playlist[] = {
     {"/97/004  hot  rats.mp3", 100, 115},
     {"/97/004  hot  rats.mp3", 120, 135},
     {"/97/004  hot  rats.mp3", 140, 155},
     {"/97/004  hot  rats.mp3", 160, 175},
     {"/97/004  hot  rats.mp3", 180, 195}
 };
 const int playlistSize = sizeof(playlist) / sizeof(playlist[0]);
 
 void Task1(void *pvParameters) {
     TickType_t lastWakeTime = xTaskGetTickCount();
     while (1) {
         Serial.print("1");
         Serial.flush();
         vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(1000));
     }
 }
 
 void Task2(void *pvParameters) {
     TickType_t lastWakeTime = xTaskGetTickCount();
     while (1) {
         Serial.print("2");
         Serial.flush();
         vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(2000));
     }
 }
 
 void Task3(void *pvParameters) {
     pinMode(LED_PIN, OUTPUT);
     TickType_t lastWakeTime = xTaskGetTickCount();
     while (1) {
         digitalWrite(LED_PIN, HIGH);
         vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(300));
 
         digitalWrite(LED_PIN, LOW);
         vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(2000));
     }
 }
 
 void Task4(void *pvParameters) {
     TickType_t lastWakeTime = xTaskGetTickCount();
     while (1) {
         Serial.println("*");
         Serial.flush();
         vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(27000));
     }
 }
 
 void Task5(void *pvParameters) {
     TickType_t lastWakeTime = xTaskGetTickCount();
     while (1) {
         timeManager.syncTime();
         String timeStr = timeManager.getLocalDateTime();
         Serial.println("Updated Local Time: " + timeStr);
         Serial.flush();
         vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(86400000)); // 24 hours
     }
 }
 
 // === NEW: Task to play a different fragment every 2 minutes ===
 void Task_PlayFragment(void *pvParameters) {
     TickType_t lastWakeTime = xTaskGetTickCount();
     while (1) {
         int trackIndex = random(0, playlistSize);
         Serial.printf("[INFO] Playing fragment: %s (%lu - %lu sec)\n",
                       playlist[trackIndex].filename,
                       playlist[trackIndex].startSec,
                       playlist[trackIndex].endSec);
 
         audioManager.playFragment(playlist[trackIndex].filename,
                                   playlist[trackIndex].startSec,
                                   playlist[trackIndex].endSec);
 
         vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(120000)); // Every 2 minutes
     }
 }
 
 void setup() {
     Serial.begin(115200);
     delay(1000);
 
     lightManager.begin();
     audioManager.begin();
 
     if (sdManager.begin(SD_CS)) {
         Serial.println("SD Card Initialized.");
         bool fileExists = sdManager.isFileExists(SD, "/97/004  hot  rats.mp3");
         Serial.printf("[INFO] Test Result: File Exists? %s\n", fileExists ? "YES" : "NO");
     } else {
         Serial.println("[ERROR] SD Card Initialization Failed!");
     }
 
     xTaskCreate(Task1, "Task 1", 2048, NULL, 1, &Task1_Handle);
     xTaskCreate(Task2, "Task 2", 2048, NULL, 2, &Task2_Handle);
     xTaskCreate(Task3, "Task 3", 2048, NULL, 2, &Task3_Handle);
     xTaskCreate(Task4, "Task 4", 2048, NULL, 1, &Task4_Handle);
     xTaskCreate(Task5, "Task 5", 4096, NULL, 3, &Task5_Handle);
     xTaskCreate(Task_PlayFragment, "Task 6", 4096, NULL, 3, &Task6_Handle);  // ✅ NEW TASK
 }
 
 void loop() {
     lightManager.updateLight();
     vTaskDelay(pdMS_TO_TICKS(1));
 }
 