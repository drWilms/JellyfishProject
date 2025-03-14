# JellyfishQueue Library

## Overview
JellyfishQueue is a custom queue implementation for managing timed events in the Jellyfish project. It provides an efficient way to store, retrieve, and process events in a structured FIFO manner.

## Features
- FIFO queue structure
- Add, remove, and fetch elements
- Supports time-based event processing
- Designed for integration with Jellyfish's tiered timer system

## Installation
Place `JellyfishQueue.h` and `JellyfishQueue.cpp` inside the `lib/JellyfishQueue` directory of your PlatformIO project.

## Usage Example
```cpp
#include "JellyfishQueue.h"

JellyfishQueue queue;

queue.addEvent(42);
int event = queue.fetchEvent();
