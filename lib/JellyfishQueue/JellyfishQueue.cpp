#include "JellyfishQueue.h"

/**
 * JellyfishQueue Implementation
 * Version: 2025-03-12
 */

JellyfishQueue::JellyfishQueue() : debugQueue(false) {}

void JellyfishQueue::enqueue(const std::string& item) {
    queue.push(item);
    if (debugQueue) {
        Serial.printf("[JellyfishQueue] Enqueued: %s at %lu ms\n", item.c_str(), millis());
    }
}

std::string JellyfishQueue::dequeue() {
    if (queue.empty()) {
        if (debugQueue) {
            Serial.printf("[JellyfishQueue] Dequeue attempted on empty queue at %lu ms\n", millis());
        }
        return "";
    }
    std::string item = queue.front();
    queue.pop();
    if (debugQueue) {
        Serial.printf("[JellyfishQueue] Dequeued: %s at %lu ms\n", item.c_str(), millis());
    }
    return item;
}

std::string JellyfishQueue::peek() const {
    if (queue.empty()) {
        if (debugQueue) {
            Serial.printf("[JellyfishQueue] Peek attempted on empty queue at %lu ms\n", millis());
        }
        return "";
    }
    if (debugQueue) {
        Serial.printf("[JellyfishQueue] Peek: %s at %lu ms\n", queue.front().c_str(), millis());
    }
    return queue.front();
}

bool JellyfishQueue::isEmpty() const {
    if (debugQueue) {
        Serial.printf("[JellyfishQueue] isEmpty check: %s at %lu ms\n", queue.empty() ? "true" : "false", millis());
    }
    return queue.empty();
}

void JellyfishQueue::clear() {
    while (!queue.empty()) {
        queue.pop();
    }
    if (debugQueue) {
        Serial.printf("[JellyfishQueue] Cleared at %lu ms\n", millis());
    }
}

size_t JellyfishQueue::size() const {
    if (debugQueue) {
        Serial.printf("[JellyfishQueue] Size check: %lu at %lu ms\n", queue.size(), millis());
    }
    return queue.size();
}

void JellyfishQueue::processQueue() {
    if (this->queue.empty()) return;  // ✅ Prevent empty queue processing

    if (this->queue.size() > 50) {  
        Serial.println("[WARNING] Queue Overflow Risk!");
    }

    std::string item = this->queue.front();
    this->queue.pop();
    if (debugQueue) {
    Serial.printf("[Queue] Processing: %s\n", item.c_str());}
}


// Debug control
void JellyfishQueue::setDebug(bool enable) {
    debugQueue = enable;
    Serial.printf("[JellyfishQueue] Debug mode %s at %lu ms\n", debugQueue ? "enabled" : "disabled", millis());
}

bool JellyfishQueue::getDebug() const {
    return debugQueue;
}
