#include "PayloadUtils.h"

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

void hexdump(const void *mem, uint32_t len, uint8_t cols) {
  const uint8_t *src = (const uint8_t *)mem;
  Serial.printf("[HEXDUMP] Address: 0x%08tX len: 0x%X (%d)", (ptrdiff_t)src,
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
