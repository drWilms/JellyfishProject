#ifndef DYNTIMER_H
#define DYNTIMER_H

#include "Arduino.h"

class DynTimer {
private:
    unsigned long interval;
    unsigned long lastRun;
    bool active;

public:
    DynTimer();  
    void start(unsigned long duration);
    void stop();
    bool isExpired();
    bool isActive() const;
};

#endif // DYNTIMER_H
