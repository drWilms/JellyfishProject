#include "FifoDeque.h"

void FifoDeque::pushBack(QueueEvent* event) {
    queue.push_back(event);
}

QueueEvent* FifoDeque::pickToken(int index) {
    if (index < queue.size()) {
        QueueEvent* event = queue[index];
        queue.erase(queue.begin() + index);
        return event;
    }
    return nullptr;
}

bool FifoDeque::isEmpty() {
    return queue.empty();
}
