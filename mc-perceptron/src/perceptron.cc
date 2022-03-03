#include <stdio.h>
#include "core-fusion.h"

// Dot product of a 4-element data vector and 4-element weight vector

void dotproduct(in_array<int16_t,4> features, out_array<int16_t,4> out) {
  int16_t coef[12] = {
    -9,  25, -28, -27,
    -3, -31,  58, -31,
    -10,   4,  80,  79
  }; // weights

  out.resize(3); // set the actual output size
  for (uint8_t i = 0; i < 3; i++) {
    int16_t acc = 0;
    for (uint8_t j = 0; j < 4; j++)
      acc += coef[4*i + j] * features[j];
    out[i] = acc;
  }
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

  int expected[] = {0, 0, 1, 2};

  for (int i = 0; i < 4; i++) {
    int16_t cls[3];
    fun(as_array(data[i], 4), as_array(cls, 3));
    printf("Ex %d = %d (%d, %d, %d)\n", i, expected[i], cls[0], cls[1], cls[2]);
  }
}