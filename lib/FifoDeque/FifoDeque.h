#ifndef FIFO_DEQUE_H
#define FIFO_DEQUE_H

#include "Arduino.h"
#include "QueueEvent.h"
#include "macros.inc"

#define DEQUE_SIZE 10

class FifoDeque {
public:
    explicit FifoDeque();
    void pushBack(QueueEvent* event);
    QueueEvent* pickToken(int index);
    QueueEvent* peekFront();
    QueueEvent* peekBack();
    bool isFull();
    int count();

private:
    QueueEvent* queue[DEQUE_SIZE];
    int frontIndex;
    int backIndex;
    int itemCount;
};

#endif // FIFO_DEQUE_H
