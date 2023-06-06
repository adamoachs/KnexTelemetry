#include <arduino.h>
#include "KnexTelemetryClient.h"

using namespace std;

KnexTelemetryClient client;

void setup() {

}

void loop() {
    client.SendSensorValue("test-sensor-0", (char*)analogRead(0));
    client.SendSensorValue("test-sensor-1", (char*)analogRead(1));
    client.SendSensorValue("test-sensor-2", (char*)analogRead(2));
    
    delay(2000);
}
