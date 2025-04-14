#include "scale.h"

Scale::Scale(int doutPin, int clkPin, long threshold)
    : doutPin(doutPin), clkPin(clkPin), threshold(threshold) {
  read = 0;
  isOverThreshold = false;
}

void Scale::setup() { scale.begin(doutPin, clkPin); }

void Scale::update() {
  read = scale.read();
  isOverThreshold = read > threshold;
}

void printWithThousandsSeparator(long num) {
  String result = "";
  int counter = 0;

  String numStr = String(num);
  int len = numStr.length();

  for (int i = len - 1; i >= 0; --i) {
    result = numStr[i] + result;
    counter++;
    if (counter % 3 == 0 && i != 0) {
      result = ',' + result; // Change ',' to '.' if needed
    }
  }

  Serial.print(result);
}

void Scale::printStatus() {
  Serial.print("Read: ");
  printWithThousandsSeparator(read);
  Serial.print(" | Threshold: ");
  Serial.print(threshold);
  Serial.print(" | Is over threshold: ");
  Serial.println(isOverThreshold);
}
