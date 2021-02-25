#define UseOTA_Password false
#define OTA_Password ""
#define chipName "your_chip_name_here"

#include <ArduinoOTA.h>
#include <ArduinoJson.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
//TODO import Wifi_libs for ESP32...
#else
#error Unsupported Board used?
#endif

/* Insert your WiFi Credentials here */
const char* ssid = "Wifi_Name";
const char* password = "Wifi_password";

/* Setup your MQTT-Broker IP (dns name should work too) */
const char* mqtt_server = "192.168.2.161";

WiFiClient espClient;
PubSubClient client(espClient);

/* Define your global Variables here */


void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String topicStr(topic);

  String msg = String((char*)payload);

  if(topicStr.equals("some_topic")) {
    if(msg.equals("1")) {
      /* do this */
    } else if(msg.equals("0")){
      /* do that */
    }
    client.publish("another_topic", (char*)payload);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = chipName;
    if (client.connect(clientId.c_str()),"status_topic", 0, false, "offline") {
      Serial.println("connected");
      client.publish("status_topic", "online");

      /* Subscribe to needed topics here */
      client.subscribe("some_topic");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  //Default Setup
  Serial.begin(115200);
  while(!Serial);
  Serial.println("\nStarting up...");

  // Setup Pins
  pinMode(led, OUTPUT);
  analogWrite(led, 0);

  // Connenct to Wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Server
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  OTAsetup();
  reconnect();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
  ArduinoOTA.handle();


  /* Here should be your main code */
  
}
