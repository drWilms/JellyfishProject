#ifndef JELLYFISHQUEUE_H
#define JELLYFISHQUEUE_H

#include <Arduino.h>

class JellyfishQueue {
private:
    static const int MAX_SIZE = 100;
    char queue[MAX_SIZE];
    int front;
    int rear;
    int count;

public:
    JellyfishQueue();

    void add(char item);  // Renamed from enqueue
    char dequeue();
    void process();       // New function
    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    // Java-style getters
    int getFrontIndex() const;
    int getRearIndex() const;
    int getCount() const;
};

#endif  // JELLYFISHQUEUE_H
