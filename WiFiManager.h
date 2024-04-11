#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "Config.h"  // Убедитесь, что Config.h включает нужные константы
#include "SettingsManager.h"

class WiFiManager {
public:
    WiFiManager(SettingsManager* settingsManager);  // Измените конструктор, чтобы он не требовал параметров
    void connect();
    void updateCredentials(const char* ssid, const char* password);
    bool loadWiFiSettings();
    bool saveWiFiSettings(const char* ssid, const char* password);

private:
    WiFiSettings settings; // Используем структуру для хранения данных
    SettingsManager* settingsManager;
};

#endif
