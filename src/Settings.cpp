#include "Settings.hpp"
#include <cstring>

//////////////////////// DELETE BEFORE COMMIT ////////////////////////
#define DEF_WIFI_SSID       "q2feidsDL"
#define DEF_WIFI_PWD        "WorkWork"
#define DEF_WIFI_IP         { 192, 168, 88, 221 }
#define DEF_HOSTNAME        "teplo"        
#define DEF_MQTT_SERVER     "192.168.88.111"
#define DEF_MQTT_USER       "mqtt"
#define DEF_MQTT_PWD        "J3E8fo9jhA2"
#define DEF_MQTT_CLIENT_ID  "ESP32-TEPLO"
#define DEF_MQTT_QUEUE      DEF_MQTT_CLIENT_ID

GeneralSettings defaultSettings = {
    .initMarker = INIT_MARKER,
    .version = VER,
    .network = {
        DEF_WIFI_SSID, DEF_WIFI_PWD, DEF_WIFI_IP, DEF_HOSTNAME, WIFI_MODE_STA
    },
    .mqtt = {
        DEF_MQTT_SERVER, DEF_MQTT_USER, DEF_MQTT_PWD, DEF_MQTT_CLIENT_ID, DEF_MQTT_QUEUE
    },
    .temp = { 0 },
    .reserved = { 0 }
};

const GeneralSettings& SettingsManager::get() {
    return defaultSettings;
};
