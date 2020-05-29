#pragma once

#include <inttypes.h>

struct MQTTSettings {
    char server[64];
    char user[32];
    char password[32];
    char clientId[64];
    char queueRoot[64];
};

struct NetworkSettings {
    /**
    * Настройки WiFi
    */
    char ssid[64];
    char password[64];
    unsigned char ipAddress[4];

    char hostName[64];

    unsigned char wifiMode;

    char reserved[128];

};

struct TempSensors {
    uint8_t t1[8];
    uint8_t t2[8];
    uint8_t tA[8];
    uint8_t t4[8];
    uint8_t td[8];
};

struct GeneralSettings {
    char initMarker[4];         // ConF
    unsigned char version;      // 1
    NetworkSettings network;
    MQTTSettings mqtt;    
};