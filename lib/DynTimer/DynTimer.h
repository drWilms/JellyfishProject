// In DynTimer.h
#ifndef DYNTIMER_H
#define DYNTIMER_H

#include <Arduino.h>
#include <functional>
#include <vector>



class DynTimer {
public:
    enum TimerState { INACTIVE, ACTIVE, COMPLETED };

private:
    unsigned long interval;
    unsigned long nextExecution;
    bool repeating;
    bool running;
    bool debugEnabled;
    std::function<void()> callback;
    TimerState state;  // Add the state to track timer status

public:
    DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating = true);
    void start();
    void stop();
    void pause();
    void resume();
    bool isReady();
    void reset();
    void update();
    void setInterval(unsigned long newInterval);

    TimerState getState() const;
    void setState(TimerState newState) { state = newState; }  // Setter for state
    bool isRunning() const { return running; }
    unsigned long getNextExecution() const { return nextExecution; }
    void setDebug(bool enable);
    bool getDebug() const;
};

class TimerManager {
private:
    std::vector<DynTimer*> timers;
    bool debugEnabled;

public:
    int addTimer(unsigned long interval, std::function<void()> callback, bool repeating = true);
    void removeTimer(DynTimer* timer);
    void updateAll();
    void stopAll();
    DynTimer* getTimer(int index);
    int getActiveTimerCount();
    void setDebug(bool enable);
    bool getDebug() const;
    void cleanupTimers();  // Cleanup function
};

extern TimerManager timerManager;

#endif // DYNTIMER_H
