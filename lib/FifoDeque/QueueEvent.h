#ifndef QUEUE_EVENT_H
#define QUEUE_EVENT_H

#include <cstring> // Ensure we have access to strncpy

enum class EventType {
    AUDIO,
    LIGHT,
    TIMER
};

struct QueueEvent {
    EventType type;
    union {
        struct {
            char filePath[64];
        } audio;
        
        struct {
            int pattern;
            int duration;
            int brightness;
        } light;
        
        struct {
            int delayMs;
        } timer;
    } data;
};

QueueEvent createAudioEvent(const char* filePath);
QueueEvent createLightEvent(int pattern, int duration, int brightness);
QueueEvent createTimerEvent(int delayMs);

#endif // QUEUE_EVENT_H
