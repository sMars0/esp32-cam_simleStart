#include "WiFiManager.h"
#include <WiFi.h>

// Инициализация статических переменных
const char* WiFiManager::m_ssid = WIFI_SSID;
const char* WiFiManager::m_password = WIFI_PASSWORD;

WiFiManager::WiFiManager() {
    // Пустой конструктор
}

void WiFiManager::connect() {
    WiFi.begin(m_ssid, m_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void WiFiManager::updateCredentials(const char* ssid, const char* password) {
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    // Сохранение новых учетных данных можно реализовать здесь
}
