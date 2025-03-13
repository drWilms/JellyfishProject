#ifndef JELLYFISHQUEUE_H
#define JELLYFISHQUEUE_H

#include <queue>
#include <functional>
#include <Arduino.h>

#define DEBUG 1
#define LOG(x) if (DEBUG) Serial.println(F(x))

class JellyfishQueue {
private:
    std::queue<std::function<void()>> taskQueue;
    std::vector<std::pair<unsigned long, std::function<void()>>> delayedTasks;

public:
    JellyfishQueue();
    void enqueue(std::function<void()> task);
    void enqueueDelayed(unsigned long delayMs, std::function<void()> task);
    void processQueue();
};

#endif
