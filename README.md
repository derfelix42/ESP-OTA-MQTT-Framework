# ESP-OTA-MQTT-Framework
Simple Framwork for the ESP8266 to use MQTT and OTA (Over-The-Air flasing)

## Things you might want to change
The following variables should be changed:
- _chipName_: Name of Chip, that will be the clientID in MQTT and the hostname for OTA
- _WiFi Credentials_
- _MQTT-Server Address_

You might want to add your code at the following positions:

The _callback_ function gets called every time, the ESP receives a message on a topic it is subscribed to. Replace "some_topic" with the topic you want to work with and work accordingly with your payload in _msg_. The _client.publish()_ is optional and is meant to send a status message back to the broker.
```
if(topicStr.equals("some_topic")) {
  if(msg.equals("1")) {
    /* do this */
  } else if(msg.equals("0")){
    /* do that */
  }
  client.publish("another_topic", (char*)payload);
}
```

The _reconnect()_ function tries to reconnect to the MQTT broker, if the connection was lost. In here you can change the _status_topic_, on which the ESP publishes "online" once connected and also "offline", as its last will (if it gets disconnected for a longer period) is executed. This is also the point in the code where the ESP subscribes to its topics, it wants to listen on - add as many `client.subscribe("some_topic")` as you need.

The mainloop is the place for your main code. Depending on what this Framework shall be used for, here you can read out sensors, change variables depending on data you got in the callback-function, send status-updates to your MQTT broker and much more!

## Using Over-The-Air updates
This is an extremly great feature with ESPs, as you can place them at any inaccessible location you want and still reprogramm them (as long as they still have good WiFi connection and power...).
You can read more on: https://arduino-esp8266.readthedocs.io/en/latest/ota_updates/readme.html
