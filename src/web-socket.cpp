#include "web-socket.h"
#include "WebSockets.h"

WebSocket::WebSocket(const char *ip, const int port) : ip(ip), port(port) {}
WebSocket::WebSocket(const char *ip, const int port, const bool verbose)
    : ip(ip), port(port), verbose(verbose) {}

char *decodeASCII(const uint8_t *payload, size_t length) {
  if (payload == nullptr || length == 0) {
    return nullptr;
  }

  char *decodedString = (char *)malloc(length + 1);
  if (decodedString == nullptr) {
    // Handle memory allocation error
    return nullptr;
  }

  for (size_t i = 0; i < length; i++) {
    decodedString[i] = (char)payload[i];
  }

  decodedString[length] = '\0';

  return decodedString;
}

void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
  const uint8_t *src = (const uint8_t *)mem;
  Serial.printf("\n[HEXDUMP] Address: 0x%08tX len: 0x%X (%d)", (ptrdiff_t)src,
                len, len);
  for (uint32_t i = 0; i < len; i++) {
    if (i % cols == 0) {
      Serial.printf("\n[0x%08tX] 0x%08X: ", (ptrdiff_t)src, i);
    }
    Serial.printf("%02X ", *src);
    src++;
  }
  Serial.printf("\n");
}

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
