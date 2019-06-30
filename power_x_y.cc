#include "test_framework/generic_test.h"

/*
 * This program returns the result of a double x to an int y power (x^y)
 *
 * Start out by doing the brute force way. So if I take 2.11 as the double and 3 as y,
 * then the answer is 2.11 * 2.11 * 2.11. In terms of where to store values while working,
 * I would need to declare a double to be returned.
 *
 * Also need to take into account that if y=0, then the answer is 1 regardless of x.
 * May also need to take into account negative exponents.
 */
double Power(double x, int y) {
    /*
  // TODO - you fill in here.
  if(y == 0) // zero exponent
  {
      return 1;
  }

  double retVal = x;
  for(int i=1; i < abs(y); i++) // absolute value to handle +/-
  {
      retVal *= x;
  }

  if(y < 0)
  {
      return (1.0/retVal);    // negative exponents are the same as positive exponents, then take 1 / result
  }
  return retVal;
     */
  // Test result of my solution:
  // Average running time:   20 us
  // Median running time:    <1 us

  //---------------------------------------------------------
  // Now let's try the book's clever implementation
  // The way to make it more efficient is by doing iterative grouping of pairs.
  // Ex.    2^12 = 2^6 * 2^6
  //        2^6 = 2^3 * 2^3
  //        2^3 = 2^2 * 2^1
  // I don't fully understand this one though

  double retVal = 1.0;
  long long power = y; // Has at least 64 bits.
  if(y < 0)
  {
      power = -power, x = 1.0 / x; // Commas seperate options
  }
  while(power)
  {
      if(power & 1) // if current power is ODD
      {
          retVal *= x;
      }
      // else current power is EVEN
      x *= x, power >>= 1;
  }
  return retVal;

  // Test results:
  // Average running time:    1 us
  // Median running time:    <1 us
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
