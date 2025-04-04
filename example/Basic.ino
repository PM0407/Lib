#include <MyIoTLib.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define PROJECT_ID "12345"
#define WIDGET_LABEL "temperatureSensor"

MyIoTLib iot;

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message received on topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    
    iot.begin(WIFI_SSID, WIFI_PASSWORD);
    
    if (iot.connect(PROJECT_ID, WIDGET_LABEL)) {
        Serial.println("Connected to IoT Platform!");
        iot.setCallback(callback);
    } else {
        Serial.println("Failed to connect!");
    }
}

void loop() {
    iot.loop();  // Ensure MQTT stays connected

    static unsigned long lastSendTime = 0;
    if (millis() - lastSendTime > 5000) {  // Send data every 5 seconds
        lastSendTime = millis();
        String data = "{\"temperature\":25.3}";
        Serial.println("Sending data: " + data);
        iot.sendData(data.c_str());
    }
}
