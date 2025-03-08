// ========================= JellyfishQueue.cpp =========================
#include "JellyfishQueue.h"

void JellyfishQueue::enqueue(const std::string& item) {
    queue.push(item);
}

std::string JellyfishQueue::dequeue() {
    if (queue.empty()) return "";
    std::string item = queue.front();
    queue.pop();
    return item;
}

std::string JellyfishQueue::peek() const {
    return queue.empty() ? "" : queue.front();
}

bool JellyfishQueue::isEmpty() const {
    return queue.empty();
}

void JellyfishQueue::clear() {
    while (!queue.empty()) {
        queue.pop();
    }
}

size_t JellyfishQueue::size() const {
    return queue.size();
}