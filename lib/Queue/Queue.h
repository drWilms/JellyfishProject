#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>

#define QUEUE_SIZE 10  // Maximum queue size

class Queue {
private:
    String items[QUEUE_SIZE];  // Stores queued messages
    int front, rear, count;

public:
    Queue();

    bool enqueue(const String& item);
    String dequeue();
    bool isEmpty();
    bool isFull();
    void printQueue();
};

#endif  // QUEUE_H
