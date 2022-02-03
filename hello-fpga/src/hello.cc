#include <stdio.h>
#include "core-fusion.h"

int16_t calc(int16_t x) {
  return 7 * x - 15;
}

int main(int argc, char *argv[]) {
  Upduino board;
  auto fun = fpga_func(board.serialIn, board.serialOut, calc);

  board.start(argc, argv);

  for (int i = 0; i < 5; i++)
    printf("calc(%d) = %d\n", i, fun(i));
}
