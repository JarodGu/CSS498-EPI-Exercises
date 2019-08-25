#include "test_framework/generic_test.h"

/*
 * Chapter 15 Recursion Boot Camp Exercise
 * Write a function that computes the euclidean
 * greatest common divisor between two numbers.
 *
 * Initial Thoughts:
 * The problem uses a math algorithm:
 * To find the GCD of x and y, if y > x,
 * then it will be the GCD of x and y-x.
 *
 * Example: GCD(156, 36) = GCD(120, 36) and so on.
 *
 * By extension, the GCD of x and y is the GCD of x and y%x
 *
 * Example: GCD(156, 36) = GCD(156%36= 12, 36) = GCD(12, 36%12= 0) = 12
 */
long long Gcd(long long x, long long y) {
    return y == 0 ? x : Gcd(y, x % y);
}
/*
 * Results:
 * Average running time:    2 us
 * Median running time:     2 us
 */

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "gcd.cc", "gcd.tsv", &Gcd, DefaultComparator{},
                         param_names);
}
