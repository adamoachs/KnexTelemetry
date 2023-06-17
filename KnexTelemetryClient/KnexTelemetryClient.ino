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

    string s0 = client.SendData("value-0", to_string(analogRead(0)));
    string s1 = client.SendData("value-1", to_string(analogRead(1)));
    string s2 = client.SendData("value-2", to_string(analogRead(2)));

    Serial.println("New Values: ");
    Serial.println(F(s0.c_str()));
    Serial.println(F(s1.c_str()));
    Serial.println(F(s2.c_str()));
    
    
    digitalWrite(LED_BUILTIN, HIGH);  
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW); 
    delay(100);  

    delay(5000);
}
