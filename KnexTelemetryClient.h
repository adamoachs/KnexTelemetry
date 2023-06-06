#pragma once
#ifndef KnexTelemetryClient_h
#define KnexTelemetryClient_h

#include <arduino.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>

class KnexTelemetryClient 
{
    public:
        int WifiStatus();
        //Default constructor; reading settings from KnexTelemetryClient.json file
        KnexTelemetryClient();

        //Alternative constructor; explicitly provide settings
        KnexTelemetryClient(String baseUrl, String accessToken, String wifi_ssid, String wifi_password);

    private:
        String _baseUrl;
        String _accessToken;
        String _wifi_ssid;
        String _wifi_password;
        int _wifiStatus;
        WiFiClient _wifiClient;

        void WiFiInit();
        void HttpRequest(String method, String url, String body);
        void GET(String path);
        void POST(String path, String body);
};

#endif