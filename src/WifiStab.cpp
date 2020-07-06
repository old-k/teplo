#include "../../../../../.platformio/packages/framework-arduinoespressif32/libraries/WiFi/src/WiFi.h"
#include "../../../../../.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp32/esp_wifi_types.h"
#include "../../../../../.platformio/packages/framework-arduinoespressif32/cores/esp32/esp32-hal.h"
#include "../../../../../.platformio/packages/framework-arduinoespressif32/cores/esp32/HardwareSerial.h"
#include "../../../../../.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp32/esp_event_legacy.h"
#include "../../../../../.platformio/packages/framework-arduinoespressif32/tools/sdk/include/mdns/mdns.h"
#include "../../../../../.platformio/packages/framework-arduinoespressif32/tools/sdk/include/tcpip_adapter/tcpip_adapter.h"
#include "WifiStab.hpp"
#include "Logger.hpp"


NetworkSettings WifiStab::settings;
WiFiClient espClient;
PubSubClient mqtt(espClient);

WifiStab::WifiStab(const NetworkSettings& stt) {
    WifiStab::settings = stt;
    
}

void WifiStab::handle() {
    if (needReconnect && !espClient.connected()){
        tryToConnectToRouter();
    }
}


void WifiStab::tryToConnectToRouter() {

    char testName[64] = { 0 };
    strncpy(testName, settings.hostName, sizeof(testName));

    LOGGER.info("Bring up the WiFi module ");

    // Остановить переподключатель, чтобы не лез
    reconnectorActive = false;

    WiFi.disconnect();
    delay(200);

    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(testName);

    WiFi.begin(settings.ssid, settings.password);

    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(testName);

    LOGGER.info("connecting to router...");

    long startedAt = millis();
    while (!WiFi.isConnected() && (millis() - startedAt < 10000)) {
        delay(20);
    }
    if (!WiFi.isConnected()) {
        // не подключились. В режим AP
        LOGGER.error("Not connected");

    } else {
        LOGGER.info("Connected to router.");
        LOGGER.info("local IP " + WiFi.localIP().toString());
        // реконнектор активировать
        reconnectorActive = true;
    }

}

void WifiStab::onWiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case SYSTEM_EVENT_STA_START:
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            LOGGER.warning("Disconnected from Wi-Fi. reconnecting...");
            needReconnect = reconnectorActive;
            break;
    }

}

void WifiStab::init() {
    LOGGER.info("init WiFi");
    delay(800);

    IPAddress ipAddress = IPAddress(settings.ipAddress[0],
                                    settings.ipAddress[1],
                                    settings.ipAddress[2],
                                    settings.ipAddress[3]);

    WiFi.onEvent(onWiFiEvent);

    LOGGER.info("WiFi  \r\nSID: " + String(settings.ssid) + "\r\n"
            " password: " + String(settings.password) + "\r\n"
                        " hostName: " + String(settings.hostName) + "\r\n"
                        " local Ip: " + ipAddress.toString() + "\r\n"
                        " Current state: " + String(WiFi.getMode()) + "\r\n"
                        " wifi mode: " + String(settings.wifiMode) + "\r\n");

    if (settings.wifiMode != WIFI_OFF) {

        LOGGER.info("Configuring WiFi...");

        tryToConnectToRouter();

        LOGGER.debug("bring up MDNS ");

        esp_err_t mDnsError = mdns_init();
        if (mDnsError){
            LOGGER.debug("mDns start error " + String(mDnsError));
        } else {
            mdns_hostname_set(settings.hostName);
            mdns_instance_name_set(settings.hostName);
            LOGGER.debug("mDns started ");
        }

        LOGGER.info("WiFi and services works fine");

    } else if (settings.wifiMode == WIFI_OFF && WiFi.getMode() != WIFI_OFF) {

        LOGGER.info("   Turning WiFi off...");
        WiFi.mode(WIFI_OFF);
        delay(1);

    }
}
