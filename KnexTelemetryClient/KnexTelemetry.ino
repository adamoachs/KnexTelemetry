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
    Serial.print(millis());
    Serial.println(" ms");

    client.SendSensorValue("test-sensor-0", (char*)analogRead(0));
    client.SendSensorValue("test-sensor-1", (char*)analogRead(1));
    client.SendSensorValue("test-sensor-2", (char*)analogRead(2));

    //Serial.println(WiFi.status());
    
    digitalWrite(LED_BUILTIN, HIGH);  
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW); 
    delay(100);  

    delay(5000);
}
