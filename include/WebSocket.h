#pragma once

#include <WebSocketsClient.h>

class WebSocket {
private:
  const char *ip;
  const int port;

  const bool verbose = false;

  WebSocketsClient webSocket;

  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);

  void errorEvent(uint8_t *payload, size_t length);
  void disconnectedEvent(uint8_t *payload, size_t lenght);
  void connectedEvent(uint8_t *payload, size_t lenght);
  void textEvent(uint8_t *payload, size_t lenght);
  void binEvent(uint8_t *payload, size_t lenght);
  void fragmentTextStartEvent(uint8_t *payload, size_t lenght);
  void fragmentBinStartEvent(uint8_t *payload, size_t lenght);
  void fragmentEvent(uint8_t *payload, size_t lenght);
  void fragmentFinEvent(uint8_t *payload, size_t lenght);
  void pingEvent(uint8_t *payload, size_t lenght);
  void pongEvent(uint8_t *payload, size_t lenght);

public:
  WebSocket(const char *ip, const int port);
  WebSocket(const char *ip, const int port, const bool verbose);

  void setup();
  void loop();
};
