#include "Settings.hpp"
#include <cstring>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

const char *CONFIG_NAME = "/config.txt";
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

#include "Settings.hpp"
#include <string.h>

const char SettingsManager::MARKER[] = { 'T', 'e', 'p', 'l' };
const int SettingsManager::VERSION = 1;

SettingsManager SettingsManager::settingsMan = SettingsManager();

SettingsManager::SettingsManager()
	: settings{
		.initMarker = {0},
		.version 	= 0,
		.network 	= {0},
		.mqtt 		= {0},
		.temp 		= {0},
		.reserved 	= {0}
} {
	memcpy(settings.initMarker, MARKER, sizeof(settings.initMarker));
	settings.version = VERSION;
}

 const SettingsManager& SettingsManager::instance() {
   return settingsMan;
 }


const GeneralSettings& SettingsManager::get() {
    return instance().settings;
};

bool SettingsManager::is_valid(const GeneralSettings& stt) {
	bool rv = memcmp(stt.initMarker, MARKER, sizeof(MARKER));
	rv &= stt.version == VERSION;
	return rv;
};

/*
int loadConfiguration(const char *filename, GeneralSettings &config) {
  // Open file for reading
  File file = SD.open(filename);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
  config.port = doc["port"] | 2731;
  strlcpy(config.hostname,                  // <- destination
          doc["hostname"] | "example.com",  // <- source
          sizeof(config.hostname));         // <- destination's capacity

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}

// Saves the configuration to a file
void saveConfiguration(const char *filename, const GeneralSettings &config) {
  // Delete existing file, otherwise the configuration is appended to the file
  SD.remove(filename);

  // Open file for writing
  File file = SD.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> doc;

  // Set the values in the document
  doc["hostname"] = config.hostname;
  doc["port"] = config.port;

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file
  file.close();
}
*/

