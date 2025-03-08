// ========================= JellyfishQueue.h =========================
#ifndef JELLYFISHQUEUE_H
#define JELLYFISHQUEUE_H

#include <queue>
#include <string>
#include <Arduino.h>

class JellyfishQueue {
private:
    std::queue<std::string> queue;

public:
    void enqueue(const std::string& item);
    std::string dequeue();
    std::string peek() const;
    bool isEmpty() const;
    void clear();
    size_t size() const;
};

#endif // JELLYFISHQUEUE_H