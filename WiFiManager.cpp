#include "WiFiManager.h"
#include <WiFi.h>

WiFiManager::WiFiManager(SettingsManager* settingsManager) : settingsManager(settingsManager) {
    if (!loadWiFiSettings()) {
        // TODO: Если настройки не загружены, определить действия (например, запуск в режиме конфигурации)
    }
}

void WiFiManager::connect() {
    WiFi.begin(settings.ssid, settings.password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void WiFiManager::updateCredentials(const char* ssid, const char* password) {
    strncpy(settings.ssid, ssid, sizeof(settings.ssid));
    strncpy(settings.password, password, sizeof(settings.password));
    saveWiFiSettings(ssid, password);
    WiFi.disconnect();
    WiFi.begin(ssid, password);
}

bool WiFiManager::loadWiFiSettings() {
    return settingsManager->load(settings);
}

bool WiFiManager::saveWiFiSettings(const char* ssid, const char* password) {
    strncpy(settings.ssid, ssid, sizeof(settings.ssid));
    strncpy(settings.password, password, sizeof(settings.password));
    return settingsManager->save(settings);
}
