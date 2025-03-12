#ifndef JELLYFISHQUEUE_H
#define JELLYFISHQUEUE_H

#include <queue>
#include <string>
#include <Arduino.h>

/**
 * JellyfishQueue - Handles event queuing and processing.
 * Version: 2025-03-12
 */

class JellyfishQueue {
private:
    std::queue<std::string> queue;
    bool debugQueue;  // Debug flag

public:
    JellyfishQueue();

    void enqueue(const std::string& item);
    std::string dequeue();
    std::string peek() const;
    bool isEmpty() const;
    void clear();
    size_t size() const;

    // New method to process queue
    void processQueue();

    // Debug control
    void setDebug(bool enable);
    bool getDebug() const;
};

#endif // JELLYFISHQUEUE_H
