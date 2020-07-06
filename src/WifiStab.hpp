#include "Settings.hpp"
#include <WiFiType.h>
#include <PubSubClient.h>

#pragma once

class WifiStab {
    private:
        static bool needReconnect;
        static bool reconnectorActive;

        static void setApMode();
        static void tryToConnectToRouter();

        static void onWiFiEvent(WiFiEvent_t event);

        void init();

        static NetworkSettings settings;
    public:
        WifiStab(const NetworkSettings& stt);
        void handle();
    
};