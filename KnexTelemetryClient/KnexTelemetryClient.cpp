//************************************************************************************
//
//KnexTelemetryClient implementation
//
//************************************************************************************

#include <ArduinoJson.h>
#include "KnexTelemetryClient.h"
#include "KnexTelemetryClient_config.h"
/*
    define in KnexTelemetryClientConfig.h:

    required defines:
    DOMAIN          domain name of api server
    ACCESS_TOKEN    access token for api
    WIFI_SSID       wifi ssid
    WIFI_PASSWORD   wifi password

    optional defines:
    VERBOSE         enable verbose Serial.print messages
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
//Returns the new varValue returned by server
string KnexTelemetryClient::SendVar(string varName, string varValue)
{
    StaticJsonDocument<200> jsonReqDoc;
    jsonReqDoc["varName"] = varName;
    jsonReqDoc["varValue"] = varValue;
    string jsonReqStr = "";
    serializeJson(jsonReqDoc, jsonReqStr);

    string responseStr = POST("/api/sendVar", jsonReqStr);

    StaticJsonDocument<200> jsonDocRes;
    deserializeJson(jsonDocRes, responseStr);
    return jsonDocRes["varValue"];
}

string KnexTelemetryClient::GetVar(string varName)
{
    GET("/api/sendVar/" + varName);
}



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
string KnexTelemetryClient::GET(string path)
{
    return HttpRequest("GET", path, "");
}

//Send POST request to given path, with given body
string KnexTelemetryClient::POST(string path, string body)
{
    return HttpRequest("POST", path, body);
}

//Http request handler
//Returns string containing JSON body. Does not return headers
string KnexTelemetryClient::HttpRequest(string method, string url, string body)
{
    if(!_wifiClient.connect(DOMAIN, 6969))
        return "";

    //Build HTTP request
    string request;
    request += method + " " + url + " " + "HTTP/1.1\r\n";
    request += "Host: " + string(DOMAIN) + "\r\n";
    request += "Connection: close\r\n";
    request += "Authorization: Bearer " + string(ACCESS_TOKEN) + "\r\n";

    if(body.length() > 0)
    {
        request += "Content-Type: application/json\r\n";
        request += "Content-Length: " + to_string(body.length()) + "\r\n";
        request += "\r\n";
        request += body;
    }
    
    request += "\r\n";

    Serial.println("Request: ");
#ifdef VERBOSE
    Serial.print(F(request.c_str()));
#else
    Serial.println(F((method + " " + url).c_str()));
    Serial.println(F(body.c_str()));
    Serial.println();
#endif

    //Send request
    _wifiClient.print(F(request.c_str()));

    //Wait for client to be available with response
    while(!_wifiClient.available());

    //Handle response
#ifdef VERBOSE
    string response = "";
#endif
    string jsonBody = "";
    bool foundOpenBrace = false;
    while (_wifiClient.available())
    {
        char c = _wifiClient.read();
#ifdef VERBOSE
        response += c;
#endif
        //Look for an opening curly brace denoting the start of the json body
        //then add everything until end of response to jsonBody
        if(c == '{')
            foundOpenBrace = true;

        if(foundOpenBrace)
            jsonBody += c;
    }

    Serial.println("Response: ");
#ifdef VERBOSE
    Serial.println(F(response.c_str()));
#else
    Serial.println(F(jsonBody.c_str()));
#endif
Serial.println();

    return jsonBody;
}


