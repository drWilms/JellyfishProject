# Jellyfish Project - TimerManager

## Doel
Het Jellyfish Project vereist een **hiërarchisch timersysteem** met **vier onafhankelijke timers** die automatisch taken afhandelen. Dit systeem moet **robuust, schaalbaar en geoptimaliseerd** zijn voor de volgende taken:

1. **High-Speed Timer** - Voor snelle LED-updates (~20-50ms interval).
2. **Medium-Speed Timer** - Voor audio-gestuurde LED-effecten (~250ms - 1s).
3. **Slow-Speed Timer** - Voor lichtshows en queue-events (~10-30s).
4. **Ultra-Slow Timer** - Voor achtergrondprocessen zoals WiFi-checks (~1 min en langer).

**Belangrijk:** Het systeem moet automatisch timers toewijzen, verlopen timers herstarten en efficiënt omgaan met callbacks zonder dat het de ESP32 overbelast.

## Werking van TimerManager

### **1. Architectuur**
De **TimerManager** gebruikt vier arrays van **DynTimers** (dynamische timers) om timers te beheren. Elke timer kan een callback-functie uitvoeren na een bepaalde tijd.

| Timer Type     | Max. Timers | Interval | Toepassing |
|---------------|------------|----------|-------------|
| High-Speed    | 5          | < 100ms  | LED-animaties |
| Medium-Speed  | 5          | 100ms - 1s | Audio-reactie |
| Slow-Speed    | 5          | 1s - 30s  | Lichtshows, print-queues |
| Ultra-Slow    | 3          | > 1 min  | WiFi-checks, remote control |


### **2. Timer-Registratie**
Een nieuwe timer wordt als volgt gestart:
```cpp
TimerManager timerManager;
timerManager.startHighSpeedTimer(20, ledUpdate);
timerManager.startMediumSpeedTimer(1000, processAudio);
timerManager.startSlowSpeedTimer(20000, processQueue);
timerManager.startUltraSlowTimer(60000, checkWiFi);
```

### **3. Automatisch Herstarten**
Wanneer een timer verloopt, wordt automatisch de corresponderende callback aangeroepen en opnieuw gestart.

```cpp
void TimerManager::updateTimers() {
    for (int i = 0; i < MAX_HIGH_TIMERS; i++) {
        if (highTimers[i].isExpired() && highCallbacks[i] != nullptr) {
            highCallbacks[i]();
            highTimers[i].start(highDurations[i]);
        }
    }
    // Zelfde principe voor Medium, Slow en Ultra-Slow timers
}
```

### **4. Debugging en Logging**
Om te controleren of timers correct functioneren, wordt bij elke timeractie een logbericht gegenereerd:
```cpp
Serial.printf("⏳ Timer %d verlopen, roep callback aan.\n", i);
Serial.printf("🔄 Timer %d herstart met %lu ms.\n", i, highDurations[i]);
```


## **Status & Vervolgstappen**
✅ TimerManager ondersteunt nu **vier onafhankelijke timers** met **automatische callbacks en herstartmechanisme**. 
⏳ Volgende stap: **Performance testen en optimaliseren voor LED-animaties en queue-systemen.**


---

**Laatste update: 2025-03-14**