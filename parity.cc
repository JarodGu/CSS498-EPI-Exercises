#include "test_framework/generic_test.h"

/*
 * Function calculates the parity bit of a 64-bit word. Parity bit
 * is 1 if there is an odd number of 1's in the word, otherwise 0.
 *
 * I'll start by implementing the simple brute force approach.
 */
short Parity(unsigned long long x) {
    /*
  short retVal = 0;
  while(x)
  {
      retVal = retVal ^ (x & 1); // check if the least significant bit is 1
      x = x >> 1; // shift the input to the right 1 bit.
  }
  return retVal;
    */

    // Implementing the clever way from the book.
    // Taking an 8-bit integer for example, we can take advantage of the CPU's
    // word-level processing instead of doing small bit-wise ops.
    // The parity of an 8-bit integer is = to XORing the first and last 4 bits,
    // which is = to XORing the first and last 2 bits,
    // which is = to XORing the first and last bit.

    x = x ^ x >> 32; // x equals the XOR of the first and last 32 bits
    x = x ^ x >> 16; // x equals the XOR of the first and last 16 bits
    x = x ^ x >> 8;
    x = x ^ x >> 4;
    x = x ^ x >> 2;
    x = x ^ x >> 1;

    // the last bit is parity bit, so we need to AND to extract it.
    x = x & 0x1;

    return x;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
