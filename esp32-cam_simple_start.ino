#include <Arduino.h>
#include <WebServer.h>
#include "SettingsManager.h"
#include "Config.h"
#include "WiFiManager.h"
#include "ModeManager.h"

WebServer server(SERVER_PORT);
SettingsManager settingsManager(0, sizeof(WiFiSettings)); // Начальный адрес и размер данных
WiFiManager wifiManager(&settingsManager);
ModeManager modeManager(SERVICE_MODE_PIN);

void setup() {
    Serial.begin(115200);
    wifiManager.connect(); // Подключение к WiFi

    server.on("/", handleRoot); // Обработчик главной страницы
    server.on("/settings", handleSettings); // Обработчик страницы настроек
    server.on("/setwifi", handleSetWiFi); // Обработчик для изменения настроек WiFi

    server.begin(); // Запуск сервера
}

void loop() {
    modeManager.checkMode(); // Проверка режима работы
    server.handleClient(); // Обработка веб-запросов
}

void handleRoot() {
    if (modeManager.isInServiceMode()) {
          WiFiSettings settings; // Создаём временный объект для хранения настроек
        // Пытаемся загрузить текущие настройки
        bool isLoaded = settingsManager.load(settings);
        String page = "<h1>Настройки Wi-Fi</h1><form action='/setwifi' method='post'>";
        page += "SSID: <input type='text' name='ssid' value='" + String(isLoaded ? settings.ssid : "") + "'><br>";
        page += "Password: <input type='password' name='password' value=''><br>";
        page += "<input type='submit' value='Обновить Wi-Fi'>";
        page += "</form>";
        server.sendHeader("Content-Type", "text/html; charset=utf-8");
        server.send(200, "text/html", page);
    } else {
        // Устанавливаем заголовок Content-Type для корректного отображения кириллицы
        server.sendHeader("Content-Type", "text/html; charset=utf-8");
        server.send(200, "text/html", "<h1>Привет мир!</h1>");
    }
}


void handleSettings() {
    WiFiSettings settings; // Создаём временный объект для хранения настроек

    // Пытаемся загрузить текущие настройки
    bool isLoaded = settingsManager.load(settings);

    // Подготавливаем HTML-страницу для вывода формы настроек
    String page = "<h1>WiFi Settings</h1><form action='/setwifi' method='post'>";
    page += "SSID: <input type='text' name='ssid' value='" + String(isLoaded ? settings.ssid : "") + "'><br>";
    page += "Password: <input type='password' name='password' value='" + String(isLoaded ? settings.password : "") + "'><br>";
    page += "<input type='submit' value='Update WiFi'>";
    page += "</form>";

    // Отправляем сформированную страницу клиенту
    server.send(200, "text/html", page);
}


void handleSetWiFi() {
    if (server.hasArg("ssid") && server.hasArg("password")) {
        String newSSID = server.arg("ssid");
        String newPassword = server.arg("password");
        if (newSSID.length() > 0 && newPassword.length() > 0) {
            wifiManager.updateCredentials(newSSID.c_str(), newPassword.c_str());
            server.send(200, "text/html", "<h1>Update Successful</h1><p>Device will reboot now.</p>");
            ESP.restart(); // Перезагрузка для применения новых настроек
        } else {
            server.send(200, "text/html", "<h1>Update Failed</h1><p>SSID and Password cannot be empty.</p>");
        }
    }
}
