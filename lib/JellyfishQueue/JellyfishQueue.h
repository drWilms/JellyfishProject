/**
 * JellyfishQueue.h - A Java-style queue system for the Jellyfish Project
 * Version: 2025-03-07
 */

 #ifndef JELLYFISH_QUEUE_H
 #define JELLYFISH_QUEUE_H
 
 #include <deque>
 #include <string>
 #include <Arduino.h>  // Required for Serial
 #include "macros.inc"
 
 class JellyfishQueue {
 private:
     std::deque<std::string> queue;
 
 public:
     JellyfishQueue();
     void enqueue(const std::string& item);
     std::string dequeue();
     std::string peek() const;
     bool isEmpty() const;
     size_t size() const;
     void clear();
 };
 
 #endif // JELLYFISH_QUEUE_H
 