#include <arduino.h>
#include "KnexTelemetryClient.h"

void setup() {
  KnexTelemetryClient client("http://192.168.86.22/knextest", "token", "No Sneps Allows", "pandasonly");
}

void loop() {
  // put your main code here, to run repeatedly:
}
