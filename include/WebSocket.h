#pragma once

#include <WebSocketsClient.h>
#include <map>

#include "NTP.h"

enum class ServerEvent {
  GMT_OFFSET,
};

class WebSocket {
private:
  const char *ip;
  const int port;

  WebSocketsClient webSocket;

  NTP *ntp;

  const bool verbose = false;

  std::map<WStype_t, const char *> verboseWStype = {
      {WStype_t::WStype_ERROR, "ERROR"},
      {WStype_t::WStype_DISCONNECTED, "DISCONNECTED"},
      {WStype_t::WStype_CONNECTED, "CONNECTED"},
      {WStype_t::WStype_TEXT, "TEXT"},
      {WStype_t::WStype_BIN, "BIN"},
      {WStype_t::WStype_FRAGMENT_TEXT_START, "FRAGMENT_TEXT_START"},
      {WStype_t::WStype_FRAGMENT_BIN_START, "FRAGMENT_BIN_START"},
      {WStype_t::WStype_FRAGMENT, "FRAGMENT"},
      {WStype_t::WStype_FRAGMENT_FIN, "FRAGMENT_FIN"},
      {WStype_t::WStype_PING, "PING"},
      {WStype_t::WStype_PONG, "PONG"},
  };

  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);
  void textEvent(uint8_t *payload);
  void verboseEvent(WStype_t type, uint8_t *payload, size_t lenght);

  std::map<std::string, ServerEvent> eventMap = {
      {"GMTOffset", ServerEvent::GMT_OFFSET},
  };

public:
  WebSocket(const char *ip, const int port, NTP *ntp);
  WebSocket(const char *ip, const int port, NTP *ntp, const bool verbose);

  void setup();
  void loop();
};
