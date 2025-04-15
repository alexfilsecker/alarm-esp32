#pragma once

#include <WebSocketsClient.h>

class WebSocket {
private:
  const char *ip;
  const int port;

  const bool verbose = false;

  WebSocketsClient webSocket;

  void hexdump(const void *mem, uint32_t len, uint8_t cols = 16);
  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);

public:
  WebSocket(const char *ip, const int port);
  WebSocket(const char *ip, const int port, const bool verbose);

  void setup();
  void loop();
};
