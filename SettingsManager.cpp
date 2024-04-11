#include "SettingsManager.h"

SettingsManager::SettingsManager(int startAddress, int dataSize)
    : _startAddress(startAddress), _dataSize(dataSize) {
    EEPROM.begin(512); // Выделите достаточно памяти для вашего проекта
}

SettingsManager::~SettingsManager() {
    EEPROM.end();
}