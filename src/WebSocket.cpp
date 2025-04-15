#include "WebSocket.h"
#include "PayloadUtils.h"
#include <ArduinoJson.h>

WebSocket::WebSocket(const char *ip, const int port, NTP *ntp)
    : ip(ip), port(port), ntp(ntp) {}

WebSocket::WebSocket(const char *ip, const int port, NTP *ntp,
                     const bool verbose)
    : ip(ip), port(port), ntp(ntp), verbose(verbose) {}

void WebSocket::verboseEvent(WStype_t type, uint8_t *payload, size_t length) {
  const char *typeStr = verboseWStype[type];
  Serial.print("\nEvent: ");
  Serial.print(typeStr);
  Serial.print(", Payload length: ");
  Serial.println(length);
  if (length > 0) {
    Serial.print("ASCII Decoded payload: ");
    Serial.println(decodeASCII(payload, length));
    // hexdump(payload, length);
  }
}

void WebSocket::textEvent(uint8_t *payload) {
  String recievedJsonString = String((char *)payload);
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, recievedJsonString);

  if (error) {
    Serial.print("JSON deserialization failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char *event = doc["event"];

  if (verbose) {
    Serial.printf("Event: %s\n", event);
  }

  // Initialize with a default value
  const std::string strEvent = std::string(event);
  if (!eventMap.count(strEvent)) {
    Serial.println("ERROR Received unknown event");
    return;
  }

  const ServerEvent serverEvent = eventMap[strEvent];

  switch (serverEvent) {
  case ServerEvent::GMT_OFFSET: {
    const int8_t offset = doc["offset"];
    ntp->setGMTOffset(offset);
    break;
  }
  }
}

void WebSocket::webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  if (verbose) {
    verboseEvent(type, payload, length);
  }

  switch (type) {
  case WStype_TEXT:
    textEvent(payload);
    break;
  case WStype_ERROR:
  case WStype_DISCONNECTED:
  case WStype_CONNECTED:
  case WStype_BIN:
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

  if (verbose) {
    Serial.println("WebSocket setted up");
  }
}

void WebSocket::loop() { webSocket.loop(); }
