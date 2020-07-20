#pragma once
#include <esp_wifi_types.h>
#include <inttypes.h>

struct MQTTSettings {
    char server[64];
    char user[32];
    char password[32];
    char clientId[64];
    char queueRoot[64];
};

struct NetworkSettings {
    char ssid[64];
    char password[64];
    unsigned char ipAddress[4];
    char hostName[64];
    wifi_mode_t wifiMode;
};

struct TempSensors {
    uint8_t t1[8];
    uint8_t t2[8];
    uint8_t tA[8];
    uint8_t t4[8];
    uint8_t td[8];
};

struct GeneralSettings {
        char initMarker[4];         // Tepl
        unsigned char version;      // 1
        NetworkSettings network;
        MQTTSettings mqtt;
        TempSensors temp;
        char reserved[128];
};

class SettingsManager {
    private:
		const static char MARKER[];
		const static int VERSION;
        static SettingsManager settingsMan;
        SettingsManager();
        GeneralSettings settings;
        int init();
    public:

        static const SettingsManager& instance();
        static const GeneralSettings& get();
        static bool is_valid(const GeneralSettings& stt);

};

