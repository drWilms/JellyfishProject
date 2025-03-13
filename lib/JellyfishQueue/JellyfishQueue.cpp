#include "JellyfishQueue.h"

JellyfishQueue::JellyfishQueue() : front(0), rear(0), count(0) {}

void JellyfishQueue::add(char item) {
    if (!isFull()) {
        queue[rear] = item;
        rear = (rear + 1) % MAX_SIZE;
        count++;
    }
}

char JellyfishQueue::dequeue() {
    if (!isEmpty()) {
        char item = queue[front];
        front = (front + 1) % MAX_SIZE;
        count--;
        return item;
    }
    return '\0'; // Return null character if empty
}

void JellyfishQueue::process() {
    while (!isEmpty()) {
        Serial.print(dequeue());
    }
}

bool JellyfishQueue::isEmpty() const {
    return count == 0;
}

bool JellyfishQueue::isFull() const {
    return count == MAX_SIZE;
}

int JellyfishQueue::size() const {
    return count;
}

int JellyfishQueue::getFrontIndex() const {
    return front;
}

int JellyfishQueue::getRearIndex() const {
    return rear;
}

int JellyfishQueue::getCount() const {
    return count;
}
