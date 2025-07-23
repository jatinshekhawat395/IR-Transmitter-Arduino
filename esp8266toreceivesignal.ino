#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>

const uint16_t recvPin = 4; // GPIO4 = D2 on NodeMCU

IRrecv irrecv(recvPin);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Ready to receive IR signals...");
}

void loop() {
  if (irrecv.decode(&results)) {
    // Print basic data
    Serial.print("Protocol: ");
    Serial.println(resultToProtocolString(&results));
    Serial.print("HEX Code: 0x");
    Serial.println(results.value, HEX);
    
    // You can print full raw data if needed:
    // Serial.println(resultToHumanReadableBasic(&results));

    irrecv.resume();  // Ready to receive next signal
  }
}
