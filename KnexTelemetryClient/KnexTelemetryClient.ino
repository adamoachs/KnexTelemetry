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

    //client.SendVar("value-0", (char*)analogRead(0));
    //client.SendVar("value-1", (char*)analogRead(1));
    ///client.SendVar("value-2", (char*)analogRead(2));
    client.SendVar("value-0", "aaa");
    client.SendVar("value-1", "bbb");
    client.SendVar("value-2", "ccc");
    
    digitalWrite(LED_BUILTIN, HIGH);  
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW); 
    delay(100);  

    delay(5000);
}
