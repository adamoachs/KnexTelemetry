//************************************************************************************
//
//KnexTelemetryClient implementation
//
//************************************************************************************

#include "KnexTelemetryClient.h"
#include "KnexTelemetryClient_config.h"
/*
    define in KnexTelemetryClientConfig.h:
    DOMAIN          domain name of api server
    ACCESS_TOKEN    access token for api
    WIFI_SSID       wifi ssid
    WIFI_PASSWORD   wifi password
*/

using namespace std;

//************************************************************************************
//
//Public methods
//
//************************************************************************************

//Constructor
KnexTelemetryClient::KnexTelemetryClient()
{

}

//Call after creation but before use. Split some init logic away from the constructor because it was crashing having this in the constructor
void KnexTelemetryClient::Init()
{
    while(millis() < 5000);

    WiFiInit();
}

//Send specified value for given sensor name
void KnexTelemetryClient::SendVar(string varName, string varValue)
{
    POST("/api/sendVar/", varValue);
    //TODO: change this back to POST after figuring out how to get POSTs working
    //GET("/api/sendVar/" + varName);
}

void KnexTelemetryClient::GetVar(string varName)
{
    GET("/api/sendVar/" + varName);
}

//TODO Expose some methods from WiFiClient (status, IP)






//************************************************************************************
//
//Private methods
//
//************************************************************************************

//Start wifi connection
void KnexTelemetryClient::WiFiInit()
{
     //Not sure if I want this value, that's just what was in the reference
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

    Serial.println(F("Successfully connected to Wifi network"));
    Serial.print(F("Obtained IP: "));
    Serial.println(WiFi.localIP());
    //TODO: exception handling?
}

//Send GET request to given path
void KnexTelemetryClient::GET(string path)
{
    HttpRequest("GET", path, "");
}

//Send POST request to given path, with given body
void KnexTelemetryClient::POST(string path, string body)
{
    HttpRequest("POST", path, body);
}

//Http request handler
void KnexTelemetryClient::HttpRequest(string method, string url, string body)
{
    if(!_wifiClient.connect(DOMAIN, 6969))
        return;

    _wifiClient.println(F((method + " " + url + " " + "HTTP/1.1").c_str()));
    _wifiClient.print("Host: ");
    _wifiClient.println(DOMAIN);
    _wifiClient.println(F("Connection: close"));
    _wifiClient.print("Authorization: Bearer ");
    _wifiClient.println(ACCESS_TOKEN);

    Serial.println("Request: ");
    Serial.println(F((method + " " + url + " " + "HTTP/1.1").c_str()));
    Serial.print("Host: ");
    Serial.println(DOMAIN);
    Serial.println(F("Connection: close"));
    Serial.print("Authorization: Bearer ");
    Serial.println(ACCESS_TOKEN);

    if(body.length() > 0)
    {
        Serial.println("Content-Type: text/plain");
        Serial.println("Content-Length: " + String(body.length()));
        Serial.println();
        Serial.println(F(body.c_str()));

        _wifiClient.println("Content-Type: text/plain");
        _wifiClient.println("Content-Length: " + String(body.length()));
        _wifiClient.println();
        _wifiClient.println(F(body.c_str()));
    }
    
    _wifiClient.println();
    Serial.println();

    //Wait for client to be available
    while(!_wifiClient.available());
    
    //Old method that outputs all headers
    string response = "";
    while (_wifiClient.available())
    {
        char c = _wifiClient.read();
        response += c;
    }

    Serial.println("Response: ");
    Serial.println(F(response.c_str()));
    Serial.println();
    
    /*
    string response = "";
    bool foundOpenBrace = false;
    while (_wifiClient.available())
    {
        char c = _wifiClient.read();
        if(c == '{')
            foundOpenBrace = true;

        if(foundOpenBrace)
            response += c;
    }
    Serial.println("Received response from server: ");
    Serial.println(F(response.c_str()));
    Serial.println();
    */
}


