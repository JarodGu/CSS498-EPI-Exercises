#include "test_framework/generic_test.h"

#include <iostream>

/*
 * Write a function to reverse the digits of an integer.
 * Example, inputting -314 returns -413
 *
 * A brute force implementation would be to convert the integer to
 * a string, create a new string by reading the original from back to front,
 * then using stoi to return it as an integer.
 *
 * My brute force implementation does NOT handle negative input
 */
long long Reverse(int x) {
  /*
   * Brute force implementation
   */
  /*
  std::string original = std::to_string(x);
  char reversed[original.length()];

  // Clear any memory values from char array
  for(int i=0; i<original.length(); i++)
  {
      reversed[i] = 0;
  }

  int index = 0; // keep count while building the reversed string
  for(int i=original.length() - 1; i>-1; i--)
  {
      reversed[index++] = original[i];
  }
  return std::atoll(reversed); // use atoll to return a long long
  */
  // --------------------------------------------
  /*
   * Now from the book, we can extract digits from an integer by doing mod 10.
   * For example, 300
   *
   * Rule:  input is k
   *        if k >= 0, then k mod 10 is the most significant digit of the result,
   *        and subsuquent digits are the reverse of k/10.
   *
   * Example:   input is 573
   *            so 573 % 10 is 3, then divide 573/10 (using integer division) to get 57.
   *            57 % 10 is 7.
   *
   * To form the proper integer output, we multiple the current return value by 10 then add
   * on the next digit.
   * Use: retVal = retVal * 10 then retVal = retVal + x % 10
   */

  long long retVal = 0;
  while(x) {
      retVal = retVal * 10 + x % 10;
      x /= 10;
  }
  return retVal;

}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
