#include "FifoDeque.h"

FifoDeque::FifoDeque() {
    frontIndex = 0;
    backIndex = 0;
    itemCount = 0;
}

void FifoDeque::pushBack(QueueEvent* event) {
    if (isFull()) {
        LOG("Queue full, cannot add event.");
        return;
    }
    queue[backIndex] = event;
    backIndex = (backIndex + 1) % DEQUE_SIZE;
    itemCount++;
}

QueueEvent* FifoDeque::pickToken(int index) {
    if (index < 0 || index >= count()) return nullptr;
    QueueEvent* selected = queue[frontIndex];
    frontIndex = (frontIndex + 1) % DEQUE_SIZE;
    itemCount--;
    return selected;
}

QueueEvent* FifoDeque::peekFront() {
    return (count() > 0) ? queue[frontIndex] : nullptr;
}

QueueEvent* FifoDeque::peekBack() {
    return (count() > 0) ? queue[backIndex] : nullptr;
}

bool FifoDeque::isFull() {
    return itemCount >= DEQUE_SIZE;
}

int FifoDeque::count() {
    return itemCount;
}
