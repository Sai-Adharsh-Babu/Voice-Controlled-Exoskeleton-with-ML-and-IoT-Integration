#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ss_id";
const char* password = "ss_pwd";
const char* serverURL = "http://192.168.1.100:5000/voice_command";  

WiFiClient client;  // Declare globally

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    sendCommand(cmd);
  }
}

void sendCommand(String cmd) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, serverURL);  
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"command\": \"" + cmd + "\"}";
    int httpCode = http.POST(payload);

    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("Server response: " + response);
    } else {
      Serial.println("Error in HTTP POST");
    }

    http.end();
  }
}
