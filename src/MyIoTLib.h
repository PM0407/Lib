#ifndef MYIOTLIB_H
#define MYIOTLIB_H

#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include <BearSSLHelpers.h>

class MyIoTLib {
public:
    MyIoTLib();
    void begin(const char* ssid, const char* password, const char* authToken);
    void setCallback(void (*callback)(char*, uint8_t*, unsigned int));
    void recieve(const char* projectId, const char* labelName,const char* authToken); 
    void send(const char* projectId, const char* labelName, const char* payload,const char* authToken);
    bool validateTopic(const char* projectId, const char* labelName, const char* authToken);

    void loop(const char* projectId, const char* labelName,const char* authToken);  
    void fetchMqttCredentials(const char* authToken);

private:
void reconnect(const char* projectId, const char* labelName,const char* authToken); 

    void reconnect(); 
    void syncTime();  

    WiFiClientSecure _wifiClient;
    PubSubClient _mqttClient;
  String _mqttServer;
  int _mqttPort;
  String _mqttUser;
  String _mqttPassword;
};

#endif
