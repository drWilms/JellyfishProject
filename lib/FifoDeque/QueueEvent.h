#ifndef QUEUE_EVENT_H
#define QUEUE_EVENT_H

struct QueueEvent {
    enum EventType { AUDIO, LIGHT, CLOCK, TIMER } type;
    union {
        struct { char filePath[32]; int startTime, endTime; } audio;
        struct { int pattern, duration, brightness; } light;
        struct { int hour, minute; } clock;
        struct { int delayMs; } timer;
    };
};

#endif // QUEUE_EVENT_H
