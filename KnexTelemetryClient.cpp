//references: https://github.com/khoih-prog/WiFiWebServer/blob/master/examples/WebClient/WebClient.ino

#include "KnexTelemetryClient.h"
#include "config.h"

using namespace std;

//**************
//Public methods
//**************

//Constructor
KnexTelemetryClient::KnexTelemetryClient()
{
    WiFiInit();
}

//Send specified value for given sensor name
void KnexTelemetryClient::SendSensorValue(string sensorName, string sensorValue)
{
    POST("/api/sensorValue/" + sensorName, sensorValue);
}

//**************
//Private methods
//**************

//Start wifi connection
void KnexTelemetryClient::WiFiInit()
{
    Serial.begin(115200); //Not sure if I want this value, that's just what was in the reference
    while (!Serial && millis() < 5000);

    Serial.print(F("Connecting to SSID: "));
    Serial.println(F(WIFI_SSID));

    _wifiStatus = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(1000);

    // attempt to connect to WiFi network
    while(_wifiStatus != WL_CONNECTED)
    {
        delay(500);
        _wifiStatus = WiFi.status();
    }
    Serial.print(F("Connected."));
    //TODO: exception handling?
}

//Send GET request to given path
void KnexTelemetryClient::GET(string path)
{
    HttpRequest("GET", DOMAIN + path, "");
}

//Send POST request to given path, with given body
void KnexTelemetryClient::POST(string path, string body)
{
    HttpRequest("POST", DOMAIN + path, body);
}

//Http request handler
void KnexTelemetryClient::HttpRequest(string method, string url, string body)
{
    if(_wifiClient.connect(DOMAIN, 80))
    {
        Serial.println(F((method + " " + url + " " + "HTTP/1.1").c_str()));
        _wifiClient.println(F((method + " " + url + " " + "HTTP/1.1").c_str()));

        Serial.println(F(strcat("Host: ", DOMAIN)));
        _wifiClient.println(F(strcat("Host: ", DOMAIN)));

        if(body.length() > 0)
        {
            //TODO: support for POSTing body
        }
        
        Serial.println(F("Connection: close"));
        _wifiClient.println(F("Connection: close"));

        Serial.println();
        _wifiClient.println();

        string response = "";
        while (_wifiClient.available())
        {
            char c = _wifiClient.read();
            response += c;
        }

        Serial.println(F(response.c_str()));
    }
}
