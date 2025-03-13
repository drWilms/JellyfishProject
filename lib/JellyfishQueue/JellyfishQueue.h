#ifndef JELLYFISHQUEUE_H
#define JELLYFISHQUEUE_H

#include <queue>
#include <string>
#include <Arduino.h>

class JellyfishQueue {
private:
    std::queue<std::string> queue;
    bool debugQueue;
public:
    JellyfishQueue();

    void enqueue(const std::string& item);
    std::string dequeue();
    std::string peek() const;
    bool isEmpty() const;
    void clear();
    size_t size() const;
    void processQueue();  // ✅ Now part of the class

    void setDebug(bool enable);
    bool getDebug() const;
};

#endif // JELLYFISHQUEUE_H
