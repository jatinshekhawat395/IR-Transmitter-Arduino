#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi credentials
const char* ssid = "Wi-not!";
const char* password = "12345678";

// IR LED pin (D2 = GPIO4)
const uint16_t kIrLedPin = 4;
IRsend irsend(kIrLedPin);

// Create a web server on port 80
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  irsend.begin(); // Start IR sender

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP address:");
  Serial.println(WiFi.localIP());

  // Define route to trigger IR command
  server.on("/send", []() {
    irsend.sendNEC(0x20DF10EF, 32); // Example: LG Power button
    server.send(200, "text/plain", "IR Signal Sent!");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
