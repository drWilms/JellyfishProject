#include "QueueEvent.h"

QueueEvent createAudioEvent(const char* filePath) {
    QueueEvent event;
    event.type = EventType::AUDIO;
    strncpy(event.data.audio.filePath, filePath, sizeof(event.data.audio.filePath) - 1);
    event.data.audio.filePath[sizeof(event.data.audio.filePath) - 1] = '\0';
    return event;
}

QueueEvent createLightEvent(int pattern, int duration, int brightness) {
    QueueEvent event;
    event.type = EventType::LIGHT;
    event.data.light.pattern = pattern;
    event.data.light.duration = duration;
    event.data.light.brightness = brightness;
    return event;
}

QueueEvent createTimerEvent(int delayMs) {
    QueueEvent event;
    event.type = EventType::TIMER;
    event.data.timer.delayMs = delayMs;
    return event;
}
