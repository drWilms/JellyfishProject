#include "JellyfishQueue.h"

JellyfishQueue::JellyfishQueue() {}

void JellyfishQueue::enqueue(std::function<void()> task) {
    taskQueue.push(task);
}

void JellyfishQueue::enqueueDelayed(unsigned long delayMs, std::function<void()> task) {
    delayedTasks.push_back({millis() + delayMs, task});
}

void JellyfishQueue::processQueue() {
    while (!taskQueue.empty()) {
        auto task = taskQueue.front();
        taskQueue.pop();
        task();
    }

    unsigned long now = millis();
    auto it = delayedTasks.begin();
    while (it != delayedTasks.end()) {
        if (now >= it->first) {
            it->second();
            it = delayedTasks.erase(it);
        } else {
            ++it;
        }
    }
}
