#ifndef CONFIG_H
#define CONFIG_H

// Настройки WiFi
// extern const char* WIFI_SSID;
// extern const char* WIFI_PASSWORD;
struct WiFiSettings {
    char ssid[32];
    char password[32];
};
// Пины
const int SERVICE_MODE_PIN = 13;  // GPIO для сервисного режима

// Параметры сервера
const int SERVER_PORT = 80;

// Другие константы
const int SOME_OTHER_CONSTANT = 42;

#endif
