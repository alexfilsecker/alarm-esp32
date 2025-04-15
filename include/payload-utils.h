#pragma once
#include <Arduino.h>

char *decodeASCII(const uint8_t *payload, size_t length);
void hexdump(const void *mem, uint32_t len, uint8_t cols = 16);
