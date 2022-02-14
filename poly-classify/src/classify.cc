#include <stdio.h>
#include "core-fusion.h"

// Classify a test point with simple two-line test
uint8_t classify(int16_t x, int16_t y) {
  auto green = -3*x + y + -52;
  auto blue = -4*x - y + 136;
  // In orange class if left of both green/blue lines
  return green > 0 && blue > 0;
}

int main(int argc, char *argv[]) {
  Upduino board;
  auto fun = fpga_func(board.serialIn, board.serialOut, classify);

  board.start(argc, argv);

  // Test data, first two orange class, last two blue class
  int16_t xdata[] = {7,  5,   10, 15};
  int16_t ydata[] = {82, 100, 70, 100};

  for (int i = 0; i < 4; i++) {
    auto x = xdata[i];
    auto y = ydata[i];
    printf("classify(%d, %d) = %d\n", x, y, fun(x, y));
  }
}