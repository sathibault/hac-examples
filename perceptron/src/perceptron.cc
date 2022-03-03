#include <stdio.h>
#include "core-fusion.h"

// Dot product of a 4-element data vector and 4-element weight vector

int16_t dotproduct(in_array<int16_t,4> features) {
  int16_t coef[] = { 3, -2,  8, 10 }; // weights

  int16_t acc = 0;
  for (int i = 0; i < 4; i++)
    acc += coef[i] * features[i];

  return acc;
}

int main(int argc, char *argv[]) {
  Upduino board;
  auto fun = fpga_func(board.serialIn, board.serialOut, dotproduct);

  board.start(argc, argv);

  // Test data: four samples, for inputs each
  int16_t data[4][4] = {
    {-18,  62, -38, -34},
    {-41,  -5, -43, -38},
    { -2, -34,   4,   0},
    { 33,  -5,  26,  46}
  };

  for (int i = 0; i < 4; i++) {
    auto y = fun(as_array(data[i], 4));
    printf("%d %d\n",i, y);
  }
}