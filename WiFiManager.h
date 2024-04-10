#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "Config.h"  // Убедитесь, что Config.h включает нужные константы

class WiFiManager {
public:
    WiFiManager();  // Измените конструктор, чтобы он не требовал параметров
    void connect();
    void updateCredentials(const char* ssid, const char* password);

private:
    static const char* m_ssid;
    static const char* m_password;
};

#endif
