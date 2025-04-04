#include "MyIotLib.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
static const char ca_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIEfjCCA2agAwIBAgIQD+Ayq4RNAzEGxQyOE8iwaDANBgkqhkiG9w0BAQsFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
QTAeFw0yNDAxMTgwMDAwMDBaFw0zMTExMDkyMzU5NTlaMGExCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IEcyMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuzfNNNx7a8myaJCtSnX/RrohCgiN9RlUyfuI
2/Ou8jqJkTx65qsGGmvPrC3oXgkkRLpimn7Wo6h+4FR1IAWsULecYxpsMNzaHxmx
1x7e/dfgy5SDN67sH0NO3Xss0r0upS/kqbitOtSZpLYl6ZtrAGCSYP9PIUkY92eQ
q2EGnI/yuum06ZIya7XzV+hdG82MHauVBJVJ8zUtluNJbd134/tJS7SsVQepj5Wz
tCO7TG1F8PapspUwtP1MVYwnSlcUfIKdzXOS0xZKBgyMUNGPHgm+F6HmIcr9g+UQ
vIOlCsRnKPZzFBQ9RnbDhxSJITRNrw9FDKZJobq7nMWxM4MphQIDAQABo4IBMDCC
ASwwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUTiJUIBiV5uNu5g/6+rkS7QYX
jzkwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUwDgYDVR0PAQH/BAQD
AgGGMHQGCCsGAQUFBwEBBGgwZjAjBggrBgEFBQcwAYYXaHR0cDovL29jc3AuZGln
aWNlcnQuY24wPwYIKwYBBQUHMAKGM2h0dHA6Ly9jYWNlcnRzLmRpZ2ljZXJ0LmNu
L0RpZ2lDZXJ0R2xvYmFsUm9vdENBLmNydDBABgNVHR8EOTA3MDWgM6Axhi9odHRw
Oi8vY3JsLmRpZ2ljZXJ0LmNuL0RpZ2lDZXJ0R2xvYmFsUm9vdENBLmNybDARBgNV
HSAECjAIMAYGBFUdIAAwDQYJKoZIhvcNAQELBQADggEBAHRBl3jN7+XHBUK0dZnu
hMdoNwD1nCROU3BTIh1TNzRI0bQ0m5+C/dCRzzlqoSAFHUlOi+OiDltWkXTzmQn6
Z8bH5PFBy5sYpc/8cNPoSzhyqcpvvEZvv/Ivc0Up+dzma7vBDJC9WrMRUUlSFSQp
kdXSmphDNkXJsgARmxzc18IN6LYMRiOWlY7RE2F900pPW60BvJHHNCX0bbSRj/Ql
bmVq8wuftBD++D+RS8K++ujpMjFBROyWfBX+woQDGsMazkmgulQdnZrdj476elOL
axRvrSgEorju1kJM7M65z2RUZrfzQYW/1rs8mRUXin6iEtad/Rv1ZI1WGYmWPyBm
pbo=
-----END CERTIFICATE-----
)EOF";
static const char ca_cert1[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIF7zCCBNegAwIBAgISA3xHNIFxoU38a9VatlSKglpHMA0GCSqGSIb3DQEBCwUA
MDMxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQwwCgYDVQQD
EwNSMTEwHhcNMjUwMjA0MTQwMTQwWhcNMjUwNTA1MTQwMTM5WjAbMRkwFwYDVQQD
DBAqLnVwLnJhaWx3YXkuYXBwMIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKC
AgEAm9qARtgSCUYQtoyYprFLbZIsdooT+AuRfxyo0sqDavcqx62+pogWD5vHzArr
i4WJvQ1bMtEoigLiaMtNCVRRTV+eHfo0+JgGfPT7nf7LnpwEOIates6vseYkDtVB
0IN7GhXrgF30qvPOjXfrWEHccyLAqUlSnn6yt8T+2MMK53T9hrEQe9vJUpQ7FDsu
LPHpdXLMAxUxEOYIhMuteByIs1+LSKvvQIzLDdfRRhm/LR/RleTO0QhvltK7D2Ie
XONQa+WZ9dQYqz7b+GURjlwBtKxg2/lDX292VL4fGpRY2msNq0D9A/pJAX2EnjzI
aVF5cYuK2cpWBZIv9am777Pt/hZK+YKgVcabDsi1qhxJ1rvkz/FUp4/PIUEwMXvX
CxFyuNYnuAcYpJ1nW+f/KfDneIc7bszgDlTX3suJjMmf0CdHlMdKgRMXmiPljzjT
3SlrbkhQSMYqJ2kix12Q4GE+bGeCWigXVQGgzetM1t0s1l3L6AH5m0dCi0T1gRyB
Q8G/NSaQmSFfYx3MZQCYkpK1UHrYJqtObQInyA+77n1ONr+joUjuJnVz+yPI0GRa
ZuI+rI2kOkZpTo3h+KDRHtrBs7k88P2ZXOCh336IN3pa6TTlovtG1+RxFXQyjsIh
X48kd39Vf+ATdH+3sHEIb8t+nP5DmL4j8TGjuDBw26OC3nkCAwEAAaOCAhMwggIP
MA4GA1UdDwEB/wQEAwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIw
DAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQUuW51rCldDafzPed4lv8xMsUT85wwHwYD
VR0jBBgwFoAUxc9GpOr0w8B6bJXELbBeki8m47kwVwYIKwYBBQUHAQEESzBJMCIG
CCsGAQUFBzABhhZodHRwOi8vcjExLm8ubGVuY3Iub3JnMCMGCCsGAQUFBzAChhdo
dHRwOi8vcjExLmkubGVuY3Iub3JnLzAbBgNVHREEFDASghAqLnVwLnJhaWx3YXku
YXBwMBMGA1UdIAQMMAowCAYGZ4EMAQIBMIIBAwYKKwYBBAHWeQIEAgSB9ASB8QDv
AHUAouMK5EXvva2bfjjtR2d3U9eCW4SU1yteGyzEuVCkR+cAAAGU0XnXhwAABAMA
RjBEAiB7iJTh4CN/IaubgvZHcvtyQUYobyg5VpI3lFzXWqVUGwIgOxXNyrgY+YDz
ch7TpfMemT/it9f4knTxOT0X5BUYayQAdgB9WR4S4XgqexxhZ3xe/fjQh1wUoE6V
nrkDL9kOjC55uAAAAZTRedeYAAAEAwBHMEUCIQDF7ZBU1YmiEsSRSkOc0dfifZhC
rIuCVFkB0c4HYiu7oQIgHj8I95vOpK2QV1jUFlqFi2hQsyNUdiS46Za6ZKo+Enww
DQYJKoZIhvcNAQELBQADggEBAGSMwx+54twjFEkyeUCtOineSI5Kr1NYu2Xqwftv
p3F6VkzEXq5kpnSQMWq1KQGD3lqqDcR1Z6VqB+MP6HSDWUPUO4BmGP9mJiCOH1GP
TmZvBX0i8tkCcJxLaXcrfUW9dIaexFYBz3mkHej0GOa9m3uvuPCgaPKbNnIiLzTj
TKWbuzWqahTVD+iJ7nIqNjZS9Iya3dDy2f0pLpybxEjmwB6a4swggtNYqyZ+zOBD
ITdG8ClyZM+fAp0MmPZegCn5ineatN4Z7mNWBF1nnaWkMBWpcAoFuyluChr9Y59Z
3dU89QEakGeTTavOOGN4cstIHpiyqfx7dr8tbWJDtw3qens=
-----END CERTIFICATE-----
)EOF";
MyIoTLib::MyIoTLib() : _mqttClient(_wifiClient) {}
void MyIoTLib::fetchMqttCredentials(const char* authToken) {
    HTTPClient http;
    WiFiClientSecure client;  // Use WiFiClientSecure instead of WiFiClient

    client.setInsecure();  // Allows HTTPS connection without certificates

    http.begin(client, "https://backen-58yt.onrender.com/api/getMqttCredentials");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + authToken); 

    int httpCode = http.GET();
    String response = http.getString();
    http.end();


    if (httpCode == 200) {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, response);
        
        if (error) {
            Serial.println("Failed to parse JSON response.");
            return;
        }

        _mqttServer = doc["mqttServer"].as<String>();
        _mqttPort = doc["mqttPort"].as<int>();
        _mqttUser = doc["mqttUser"].as<String>();
        _mqttPassword = doc["mqttPassword"].as<String>();


    } else {
        Serial.print("Failed to fetch MQTT credentials. HTTP Code: ");
        Serial.println(httpCode);
    }
}


void MyIoTLib::begin(const char* ssid, const char* password, const char* authToken) {
    Serial.print("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to Wi-Fi");

    syncTime();
    fetchMqttCredentials(authToken); 
    BearSSL::X509List* caCertList = new BearSSL::X509List(ca_cert);
    _wifiClient.setTrustAnchors(caCertList);

    _mqttClient.setServer(_mqttServer.c_str(), _mqttPort);
}
void MyIoTLib::syncTime() {
    configTime(0, 0, "pool.ntp.org");

    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2) {
        delay(1000);
        Serial.print(".");
        now = time(nullptr);
    }

}

void MyIoTLib::setCallback(void (*callback)(char*, uint8_t*, unsigned int)) {
    _mqttClient.setCallback(callback);
}

void MyIoTLib::publishToDynamicTopic(const char* projectId, const char* labelName, const char* payload,const char* authToken) { 
    if (!_mqttClient.connected()) {
        reconnect(projectId, labelName,authToken);
    }

    String topic = "mqtt-subscription-mqttjs_" + String(projectId) + "_" + String(labelName) + "_qos1";
    
    if (_mqttClient.publish(topic.c_str(), payload)) {
        Serial.print("Published to topic: ");
        Serial.print("Message: ");
        Serial.println(payload);
    } else {
        Serial.println("Publishing failed!");
    }
}

void MyIoTLib::subscribeToDynamicTopic(const char* projectId, const char* labelName,const char* authToken) {    
    if (!_mqttClient.connected()) {
        reconnect(projectId, labelName,authToken);
    }

    String topic = "null_" + String(projectId) + "_" + String(labelName);
    if (_mqttClient.subscribe(topic.c_str())) {
        Serial.print("Subscribed to topic: ");

    } else {
        Serial.println("Subscription failed!");
    }
}

void MyIoTLib::loop(const char* projectId, const char* labelName,const char* authToken) {
    if (!_mqttClient.connected()) {
        reconnect(projectId, labelName,authToken);
    }
    _mqttClient.loop();
}
bool MyIoTLib::validateTopic(const char* projectId, const char* labelName, const char* authToken) {
    HTTPClient http;
    WiFiClientSecure client;  // Use Secure Client

    client.setInsecure();  // Allows connection without certificates

    String payload = "{\"projectId\": \"" + String(projectId) + "\", \"labelName\": \"" + String(labelName) + "\"}";

    http.begin(client, "https://backen-58yt.onrender.com/api/validateTopic");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + authToken);

    int httpCode = http.POST(payload);
    String response = http.getString();
    http.end();

  

    if (httpCode == 200) {
        Serial.println("Validation Successful");
        return true; 
    } else {
        Serial.print("Validation Failed! HTTP Code: ");
        Serial.println(httpCode);
        
        if (httpCode == 400) {
            Serial.println("Error: The request was sent to an HTTPS port instead of HTTP.");
        } else if (httpCode == -1) {
            Serial.println("Error: No response received. Check internet connection or server URL.");
        }

        Serial.println("Response: " + response);
        return false;
    }
}



void MyIoTLib::reconnect(const char* projectId, const char* labelName, const char* authToken) {
    if (!validateTopic(projectId, labelName, authToken)) {
        Serial.println("Invalid Project ID or Label Name. MQTT connection aborted.");
        return;
    }

    while (!_mqttClient.connected()) {
        String clientId = "ESP8266Client-" + String(WiFi.macAddress());
        if (_mqttClient.connect(clientId.c_str(), _mqttUser.c_str(), _mqttPassword.c_str())) {
            Serial.println("Connected with corex");
        } else {
            Serial.print("Failed to connect, rc=");
            Serial.print(_mqttClient.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}
void MyIoTLib::reconnect() {
    Serial.println("reconnect() called without parameters. Skipping MQTT connection.");
}