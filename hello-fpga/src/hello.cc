#include <stdio.h>

// Include FPGA programming framework
#include "core-fusion.h"

// Function to implement on FPGA
int16_t calc(int16_t x) {
  return 7 * x - 15;
}

int main(int argc, char *argv[]) {
  // Create an instance of target FPGA board class
  Upduino board;

  // Transform the calc C function into an FPGA function
  // The serialIn/serialOut parameters indicate how to communication with the board
  // from the computer in order to call the FPGA function.
  auto fun = fpga_func(board.serialIn, board.serialOut, calc);

  // Must start the board after all FPGA functions have been created
  board.start(argc, argv);

  for (int i = 0; i < 5; i++) {
    // Call the FPGA function
    // (sends the input over the serialIn port and captures the output from serialOut)
    printf("calc(%d) = %d\n", i, fun(i));
  }

  // Stop the board before exiting
  board.stop();
}
