#ifndef FIFODEQUE_H
#define FIFODEQUE_H

#include <deque>
#include "QueueEvent.h"

class FifoDeque {
private:
    std::deque<QueueEvent*> queue;

public:
    void pushBack(QueueEvent* event);
    QueueEvent* pickToken(int index);
    bool isEmpty();
};

#endif // FIFODEQUE_H
