#ifndef DYNTIMER_H
#define DYNTIMER_H

#include <Arduino.h>
#include <functional>
#include <vector>

class DynTimer {
private:
    unsigned long interval;
    unsigned long nextExecution;
    bool repeating;
    bool running;
    bool debugEnabled;
    std::function<void()> callback;

public:
    DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating = true);
    void start();
    void stop();
    void pause();
    void resume();
    bool isReady();
    void reset();
    void update();
    void setInterval(unsigned long newInterval);  // ✅ New function

    bool isRunning() const { return running; }
    unsigned long getNextExecution() const { return nextExecution; }
    void setDebug(bool enable);
    bool getDebug() const;
};

class TimerManager {
private:
    std::vector<DynTimer*> timers;

public:
    int addTimer(unsigned long interval, std::function<void()> callback, bool repeating = true);
    void removeTimer(int index);
    void updateAll();
    void stopAll();
    DynTimer* getTimer(int index);  // ✅ New function
};

#endif // DYNTIMER_H
