//************************************************************************************
//
//KnexTelemetryClient headers
//
//************************************************************************************

#ifndef KnexTelemetryClient_h
#define KnexTelemetryClient_h

#include <arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <sstream>

using namespace std;

class KnexTelemetryClient 
{
    public:
        //public fields

        //public methods
        KnexTelemetryClient(); 
        void Init();
        void SendVar(string varName, string varValue);
        void GetVar(string varName);

    private:
        //private fields
        int _wifiStatus;
        WiFiClient _wifiClient;

        //private methods
        void WiFiInit();
        void HttpRequest(string method, string url, string body);
        void GET(string path);
        void POST(string path, string body);
        string ParseResponse(string response);
        
};

#endif //KnexTelemetryClient_h