#include "WebSocket.h"
#include "PayloadUtils.h"

WebSocket::WebSocket(const char *ip, const int port) : ip(ip), port(port) {}
WebSocket::WebSocket(const char *ip, const int port, const bool verbose)
    : ip(ip), port(port), verbose(verbose) {}

void WebSocket::errorEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("Error: %s\n", decodeASCII(payload, length));
  }
};

void WebSocket::disconnectedEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.println("Socket Disconnected");
  }
};

void WebSocket::connectedEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("Socket connected to url: \"%s\"\n", payload);
  }
};

void WebSocket::textEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("Text: %s\n", payload);
  }
};

void WebSocket::binEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("Bin: %s\n", payload);
  }
};

void WebSocket::fragmentTextStartEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("FragmentTextStart: %s\n", payload);
  }
};

void WebSocket::fragmentBinStartEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("FragmentBinStart: %s\n", payload);
  }
};

void WebSocket::fragmentEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("Fragment: %s\n", payload);
  }
};

void WebSocket::fragmentFinEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("FragmentFin: %s\n", payload);
  }
};

void WebSocket::pingEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.print("Ping ");
    Serial.println(length);

    if (length > 0) {
      Serial.println(*payload);
      hexdump(payload, length);
      Serial.println(decodeASCII(payload, length));
    }
  }
};

void WebSocket::pongEvent(uint8_t *payload, size_t length) {
  if (verbose) {
    Serial.printf("Pong: %s\n", payload);
  }
};

void WebSocket::webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
  case WStype_ERROR:
    errorEvent(payload, length);
    break;
  case WStype_DISCONNECTED:
    disconnectedEvent(payload, length);
    break;
  case WStype_CONNECTED:
    connectedEvent(payload, length);
    break;
  case WStype_TEXT:
    textEvent(payload, length);
    break;
  case WStype_BIN:
    binEvent(payload, length);
    break;
  case WStype_FRAGMENT_TEXT_START:
    fragmentTextStartEvent(payload, length);
    break;
  case WStype_FRAGMENT_BIN_START:
    fragmentBinStartEvent(payload, length);
    break;
  case WStype_FRAGMENT:
    fragmentEvent(payload, length);
    break;
  case WStype_FRAGMENT_FIN:
    fragmentFinEvent(payload, length);
    break;
  case WStype_PING:
    pingEvent(payload, length);
    break;
  case WStype_PONG:
    pongEvent(payload, length);
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
