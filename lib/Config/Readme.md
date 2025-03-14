# Config Library

## Overview
The `Config` module handles configuration storage and retrieval for the Jellyfish project. It provides an interface to manage settings persistently.

## Features
- Load and save settings from persistent storage
- Modify individual parameters dynamically
- Reset configuration to default values

## Installation
Place `config.h` and `config.cpp` inside the `lib/config` directory of your PlatformIO project.

## Usage Example
```cpp
#include "config.h"

Config config;

config.setParameter("brightness", 150);
int brightness = config.getParameter("brightness");
config.saveConfig();
