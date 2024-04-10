#include "ModeManager.h"
#include <Arduino.h>

ModeManager::ModeManager(int serviceModePin) : m_serviceModePin(serviceModePin), m_inServiceMode(false) {
    pinMode(m_serviceModePin, INPUT_PULLUP);
}

void ModeManager::checkMode() {
    if (digitalRead(m_serviceModePin) == LOW) {
        if (!m_inServiceMode) {
            enterServiceMode();
        }
    } else {
        if (m_inServiceMode) {
            exitServiceMode();
        }
    }
}

bool ModeManager::isInServiceMode() const {
    return m_inServiceMode;
}

void ModeManager::enterServiceMode() {
    Serial.println("Entering service mode...");
    m_inServiceMode = true;
}

void ModeManager::exitServiceMode() {
    Serial.println("Exiting service mode...");
    m_inServiceMode = false;
}
