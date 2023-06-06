//references: https://github.com/khoih-prog/WiFiWebServer/blob/master/examples/WebClient/WebClient.ino

#include "KnexTelemetryClient.h"

//**************
//Public methods
//**************

KnexTelemetryClient::KnexTelemetryClient()
{
    String baseUrl;
    String accessToken;
    String wifi_ssid;
    String wifi_password;

    //TODO: read settings from config file

    this->_baseUrl = baseUrl;
    this->_accessToken = accessToken;
    this->_wifi_ssid = wifi_ssid;
    this->_wifi_password = wifi_password;

    WiFiInit();
}

KnexTelemetryClient::KnexTelemetryClient(String baseUrl, String accessToken, String wifi_ssid, String wifi_password)
{   
    this->_baseUrl = baseUrl;
    this->_accessToken = accessToken;
    this->_wifi_ssid = wifi_ssid;
    this->_wifi_password = wifi_password;

    WiFiInit();
}


//**************
//Private methods
//**************

void KnexTelemetryClient::WiFiInit()
{
    Serial.begin(115200);
    while (!Serial && millis() < 5000);

    Serial.print(F("Connecting to SSID: "));
    Serial.println(_wifi_ssid);

    _wifiStatus = WiFi.begin(_wifi_ssid.c_str(), _wifi_password.c_str());
    delay(1000);

    // attempt to connect to WiFi network
    while(_wifiStatus != WL_CONNECTED)
    {
        delay(500);
        _wifiStatus = WiFi.status();
    }

    //TODO: exception handling?
}

void KnexTelemetryClient::GET(String path)
{

    HttpRequest("GET", this->_baseUrl + path, "");
}

void KnexTelemetryClient::POST(String path, String body)
{
    HttpRequest("POST", this->_baseUrl + path, body);
}

void HttpRequest(String method, String url, String body)
{
    if(client.connect())
}
