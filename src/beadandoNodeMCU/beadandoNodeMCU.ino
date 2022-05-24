#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>

// Replace with your network credentials
const char* ssid = "ESP2866-AP";
const char* password = "Password";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create a WebSocket object

AsyncWebSocket ws("/ws");

// Initialize LittleFS
void initFS() {
  if (!LittleFS.begin()) {
    Serial.println("Debug: An error has occurred while mounting LittleFS");
  }
  else{
   Serial.println("Debug: LittleFS mounted successfully");
  }
}

// Initialize WiFi
void initWiFi() {
  WiFi.softAP(ssid, password);
  Serial.print("Debug: Starting WiFi network ..");
  IPAddress IP = WiFi.softAPIP();
  Serial.println("Debug: AP IP Address: ");
  Serial.println(IP);
}

void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String message = (char*)data;
    Serial.println(message);
  }
}
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("Debug: WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("Debug: WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup() {
  Serial.begin(115200);
  initFS();
  initWiFi();

  initWebSocket();
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });
  
  server.serveStatic("/", LittleFS, "/");
  server.begin();
}

void loop() {
  ws.cleanupClients();
}
