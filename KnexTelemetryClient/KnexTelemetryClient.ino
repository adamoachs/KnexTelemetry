//************************************************************************************
//
//Example code on how to use the KnexTelemetryClient class
//
//************************************************************************************

#include <arduino.h>
#include "KnexTelemetryClient.h"

using namespace std;

KnexTelemetryClient client;

void setup() {
    Serial.begin(9600);

    client.Init();
}

void loop() {
    Serial.print("Loop at: ");
    Serial.println(WiFi.getTime());

    client.SendData("lift-1-rpm", to_string(random(100,200)));
    client.SendData("lift-2-rpm", to_string(random(100,200)));
    client.SendData("lift-3-rpm", to_string(random(100,200)));

    client.SendData("lift-1-balls-in-last-hour", to_string(random(100,200)));
    client.SendData("lift-2-balls-in-last-hour", to_string(random(100,200)));
    client.SendData("lift-3-balls-in-last-hour", to_string(random(100,200)));

    client.SendStatus("lift-1-status", random(0,2) == 0 ? "offline" : "online");
    client.SendStatus("lift-2-status", random(0,2) == 0 ? "offline" : "online");    
    client.SendStatus("lift-3-status", random(0,2) == 0 ? "offline" : "online");
    
    digitalWrite(LED_BUILTIN, HIGH);  
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW); 
    delay(100);  

    delay(5000);
}
