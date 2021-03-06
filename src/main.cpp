#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Logger.hpp"
#include "WifiStab.hpp"
#include "Settings.hpp"

/* Wifi */
const char *ssid = "q2feidsDL";
const char *password = "WorkWork";
/* this is the IP of PC/raspberry where you installed MQTT Server 
on Wins use "ipconfig" 
on Linux use "ifconfig" to get its IP address */
const char *mqtt_server = "192.168.88.111";
const char *mqtt_user = "mqtt";
const char *mqtt_password = "J3E8fo9jhA2";
const char* clientId = "ESP32-TEPLO";
/* topics */
#define TEMP_TOPIC "smarthome/room1/temp"
#define LED_TOPIC "smarthome/room1/led" /* 1=on, 0=off */
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 26
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
const int PIN = 25;

/* create an instance of PubSubClient client */
//WiFiClient espClient;
WifiStab wifi(SettingsManager::get().network);
PubSubClient* client = wifi.getMQTT();


void receivedCallback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message received: ");
  Serial.println(topic);

  Serial.print("payload: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  /* we got '1' -> on */
  if ((char)payload[0] == '1')
  {
    //digitalWrite(led, HIGH);
  }
  else
  {
    /* we got '0' -> on */
    //digitalWrite(led, LOW);
  }
}

void mqttconnect()
{
  /* Loop until reconnected */
  while (!client.connected())
  {
    Serial.print("MQTT connecting ...");
    /* client ID */
    /* connect now */
    if (client.connect(clientId, mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      /* subscribe topic with default QoS 0*/
      client.subscribe(LED_TOPIC);
    }
    else
    {
      Serial.print("failed, status code =");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      /* Wait 5 seconds before retrying */
      delay(5000);
    }
  }
}

void TaskBlink1(void *pvParameters)
{
  pinMode(PIN, OUTPUT);
  while (1)
  {
    digitalWrite(PIN, HIGH);
    vTaskDelay(1200 / portTICK_PERIOD_MS);
    digitalWrite(PIN, LOW);
    vTaskDelay(1200 / portTICK_PERIOD_MS);
    //Serial.println("BLINK");
  }
}

QueueHandle_t tempQ;


void askTempTask(void *pvParameters)
{
  while (1)
  {
    sensors.requestTemperatures(); // Send the command to get temperature readings
    float t = sensors.getTempCByIndex(0);
    xQueueSend(tempQ, &t, 0);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}

long lastMsg = 0;
char msg[64];



void setup()
{
  Serial.begin(9600);
  LOGGER.info(">>>>>>>>>>Logger test");
  Serial.println("Dallas Temperature IC Control Library Demo");
  // Start up the library
  sensors.begin();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* configure the MQTT server with IPaddress and port */
  client.setServer(mqtt_server, 1883);
  /* this receivedCallback function will be invoked 
  when client received subscribed topic */
  client.setCallback(receivedCallback);


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  tempQ = xQueueCreate(10, sizeof(float));

  xTaskCreate(TaskBlink1, "Blink", 8048, NULL, 1, NULL);
  xTaskCreate(askTempTask, "mqttTask", 8048, NULL, 1, NULL);
  //vTaskStartScheduler();


}

float tempBuf = 0;
void loop()
{
    /* if client was disconnected then try to reconnect again */
    if (!client.connected())
    {
      mqttconnect();
    }
    /* this function will listen for incomming 
    subscribed topic-process-invoke receivedCallback */
    client.loop();

    long now = millis();
    //if (now - lastMsg > 3000)
    if (true)
    {
      lastMsg = now;
      if (xQueueReceive(tempQ, &tempBuf, 1) == pdTRUE) {
        LOGGER.info(" Requesting temperatures...");
        LOGGER.warning("DONE");
        /********************************************************************/
        LOGGER.error("Temperature is: ");
        snprintf (msg, sizeof(msg), "{ \"t\": %lf }", tempBuf);
        client.publish(TEMP_TOPIC, msg);

      }
    }
}