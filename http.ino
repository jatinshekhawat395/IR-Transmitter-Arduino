#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Wi-not!";
const char* password = "12345678";

const uint16_t kIrLedPin = 4; // GPIO4 (D2)
IRsend irsend(kIrLedPin);

ESP8266WebServer server(80);

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>IR Remote</title>
  <style>
    body { font-family: sans-serif; text-align: center; margin-top: 50px; }
    button {
      padding: 15px 30px;
      font-size: 18px;
      margin: 10px;
      border: none;
      background-color: #4CAF50;
      color: white;
      border-radius: 10px;
      cursor: pointer;
    }
    button:hover {
      background-color: #45a049;
    }
  </style>
</head>
<body>
  <h1>ESP8266 IR Remote</h1>
  <button onclick="send('power')">Power</button>
  <button onclick="send('volup')">Vol +</button>
  <button onclick="send('voldown')">Vol -</button>

  <script>
    function send(cmd) {
      fetch('/' + cmd)
        .then(response => response.text())
        .then(text => alert(text))
        .catch(err => alert('Error: ' + err));
    }
  </script>
</body>
</html>
)=====";

void setup() {
  Serial.begin(115200);
  irsend.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected! IP:");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send_P(200, "text/html", MAIN_page);
  });

  server.on("/power", []() {
    irsend.sendNEC(0x20DF10EF, 32); // Replace with your power code
    server.send(200, "text/plain", "Power Sent");
  });

  server.on("/volup", []() {
    irsend.sendNEC(0x20DF40BF, 32); // Replace with vol up code
    server.send(200, "text/plain", "Volume Up Sent");
  });

  server.on("/voldown", []() {
    irsend.sendNEC(0x20DFC03F, 32); // Replace with vol down code
    server.send(200, "text/plain", "Volume Down Sent");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
