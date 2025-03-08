/**
 * JellyfishQueue.cpp - Implementation of JellyfishQueue
 */

 #include "JellyfishQueue.h"
 #include "macros.inc"  
 
 /** Constructor */
 JellyfishQueue::JellyfishQueue() {}
 
 /** Add an item to the queue */
 void JellyfishQueue::enqueue(const std::string& item) {
     queue.push_back(item);
     LOG("Enqueued: ", item.c_str());
 }
 
 /** Remove and return the first item from the queue */
 std::string JellyfishQueue::dequeue() {
     if (queue.empty()) {
         LOG("Queue is empty");
         return "";
     }
     std::string item = queue.front();
     queue.pop_front();
     LOG("Dequeued: ", item.c_str());
     return item;
 }
 
 /** Peek at the first item without removing it */
 std::string JellyfishQueue::peek() const {
     if (queue.empty()) return "";
     return queue.front();
 }
 
 /** Check if the queue is empty */
 bool JellyfishQueue::isEmpty() const {
     return queue.empty();
 }
 
 /** Get the current queue size */
 size_t JellyfishQueue::size() const {
     return queue.size();
 }
 
 /** Clear the queue */
 void JellyfishQueue::clear() {
     queue.clear();
     LOG("Queue cleared");
 }
 