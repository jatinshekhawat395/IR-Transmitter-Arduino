#include <IRremote.h>

const int recv_pin = 11;  // IR Receiver pin
const int ledPin = 3;     // LED connected to digital pin 3

// Actual remote button codes (from your serial monitor)
unsigned long fanOffCode = 0x748BBF40;  // FAN OFF
unsigned long fanOnCode = 0x738CBF40;   // FAN ON

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(recv_pin, ENABLE_LED_FEEDBACK);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long receivedCode = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("Received code: 0x");
    Serial.println(receivedCode, HEX);

    if (receivedCode == fanOnCode) {
      Serial.println("FAN ON Button Pressed → LED ON");
      digitalWrite(ledPin, HIGH);
    }
    else if (receivedCode == fanOffCode) {
      Serial.println("FAN OFF Button Pressed → LED OFF");
      digitalWrite(ledPin, LOW);
    }

    IrReceiver.resume();
  }
}
