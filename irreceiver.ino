#include <IRremote.h>

#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Ready to receive Blue Star IR signal...");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println("----- RAW IR DATA -----");
    
    // Print the raw timing array
    Serial.print("uint16_t rawData[] = {");
    for (uint16_t i = 1; i < IrReceiver.decodedIRData.rawDataPtr->rawlen; i++) {
      Serial.print(IrReceiver.decodedIRData.rawDataPtr->rawbuf[i] * 50); // Convert to microseconds (tick = 50us)
      if (i < IrReceiver.decodedIRData.rawDataPtr->rawlen - 1) {
        Serial.print(", ");
      }
    }
    Serial.println("};");

    Serial.print("Length: ");
    Serial.println(IrReceiver.decodedIRData.rawDataPtr->rawlen - 1);
    Serial.println("------------------------");

    IrReceiver.resume();  // Ready for next
  }
}
