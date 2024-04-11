#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <EEPROM.h>
#include <Arduino.h>

class SettingsManager {
public:
    SettingsManager(int startAddress, int dataSize);
    ~SettingsManager();

    template <typename T>
    bool save(const T& data) {
        if (sizeof(T) > _dataSize) {
            return false;
        }
        EEPROM.put(_startAddress, data);
        return EEPROM.commit();
    }

    template <typename T>
    bool load(T& data) {
        EEPROM.get(_startAddress, data);
        return true;
    }

private:
    int _startAddress;
    int _dataSize;
};

#endif
