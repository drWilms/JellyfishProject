#include "FifoDeque.h"
#include "SWTimer.h"
#include "SWTimerManager.h"
#include "JellyfishLEDs.h"
#include "config.h"  // ✅ Ensure correct settings are used

FifoDeque eventQueue;
SWTimer eventTimer(EVENT_PROCESS_INTERVAL);
SWTimer ledEffectTimer(0);
JellyfishLEDs leds;

void processQueueEvent() {
    if (eventQueue.count() > 0) {
        QueueEvent* nextEvent = eventQueue.pickToken(0);
        if (nextEvent) {
            switch (nextEvent->type) {
                case QueueEvent::AUDIO:
                LOG("Playing audio: %s", nextEvent->audio.filePath);

                    break;
                case QueueEvent::LIGHT:
                    LOG("Starting light show pattern:", nextEvent->light.pattern);
                    leds.startEffect(nextEvent->light.pattern, nextEvent->light.duration, nextEvent->light.brightness);
                    ledEffectTimer.setInterval(nextEvent->light.duration);
                    ledEffectTimer.start();
                    break;
                case QueueEvent::CLOCK:
                    LOG("Speaking time:", nextEvent->clock.hour, ":", nextEvent->clock.minute);
                    break;
                case QueueEvent::TIMER:
                    LOG("Waiting for", nextEvent->timer.delayMs, "ms");
                    eventTimer.setInterval(nextEvent->timer.delayMs);
                    eventTimer.start();
                    break;
            }
            delete nextEvent;
        }
    }

    eventTimer.reset();
}

void handleLEDTimeout() {
    if (ledEffectTimer.isReady()) {
        LOG("LED effect duration ended, clearing LEDs.");
        leds.clearEffect();  // ✅ Now properly managed
        ledEffectTimer.stop();
    }
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    LOG("🚀 Jellyfish Project: Startup");
    leds.begin();
    eventTimer.start();

    QueueEvent* ledEvent = new QueueEvent;
    ledEvent->type = QueueEvent::LIGHT;
    ledEvent->light.pattern = 1;
    ledEvent->light.duration = LED_EFFECT_DURATION;  // ✅ From config.h
    ledEvent->light.brightness = DEFAULT_BRIGHTNESS;
    eventQueue.pushBack(ledEvent);

    LOG("Queue initialized with test events.");
}

void loop() {
    if (eventTimer.isReady()) {
        processQueueEvent();
    }
    handleLEDTimeout();
}
