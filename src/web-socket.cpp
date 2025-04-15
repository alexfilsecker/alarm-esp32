#include "web-socket.h"

WebSocket::WebSocket(const char *ip, const int port) : ip(ip), port(port) {}
WebSocket::WebSocket(const char *ip, const int port, const bool verbose)
    : ip(ip), port(port), verbose(verbose) {}

void WebSocket::webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {

  switch (type) {
  case WStype_DISCONNECTED:
    Serial.printf("[WSc] Disconnected!\n");
    break;
  case WStype_CONNECTED:
    Serial.printf("[WSc] Connected to url: %s\n", payload);

    // send message to server when Connected
    webSocket.sendTXT("hooola");
    break;
  case WStype_TEXT:
    Serial.printf("[WSc] get text: %s\n", payload);

    // send message to server
    break;
  case WStype_BIN:
    Serial.printf("[WSc] get binary length: %zu\n", length);

    // send data to server
    // webSocket.sendBIN(payload, length);
    break;
  case WStype_ERROR:
  case WStype_FRAGMENT_TEXT_START:
  case WStype_FRAGMENT_BIN_START:
  case WStype_FRAGMENT:
  case WStype_FRAGMENT_FIN:
  case WStype_PING:
  case WStype_PONG:
    break;
  }
}

void WebSocket::setup() {
  if (verbose) {
    Serial.println("setting up websocket");
  }
  webSocket.begin(ip, port);
  webSocket.onEvent([this](WStype_t type, uint8_t *payload, size_t length) {
    this->webSocketEvent(type, payload, length);
  });
}

void WebSocket::loop() { webSocket.loop(); }
