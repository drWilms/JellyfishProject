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
    std::function<void()> callback;
    static std::vector<DynTimer*> activeTimers;

public:
    DynTimer(unsigned long intervalMs, std::function<void()> callback, bool repeating = true);

    void start();
    void stop();   // 🛑 Nieuw: Stop een lopende timer
    void pause();  // ⏸ Nieuw: Pauzeer een timer zonder te stoppen
    void resume(); // ▶️ Nieuw: Hervat een gepauzeerde timer
    bool isReady();
    void reset();
    void update();
    bool isRunning() const { return running; }
    unsigned long getNextExecution() const { return nextExecution; }
    
    static void addTimer(DynTimer* timer);
    static void updateAll(); // 🔄 Update alle actieve timers
};

#endif // DYNTIMER_H
