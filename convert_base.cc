#include <string>
#include "test_framework/generic_test.h"

using std::string;

/*
 * Exercise 6.2 - Base Conversion
 * Write a function to convert a string in base b1 into a returned string in base b2
 *
 * Initial Thoughts:
 * It is easiest to convert from base10 to another base. Just keep dividing
 * by b2 and the remainder is the value added to the return string. If the number is NOT
 * in base 10, then I might need to convert it first (can use the function itself).
 * How would I represent digits past 9? Maybe I can use characters like in hex, so 10 == A...
 */

// Helper function to convert a char from '0' to 'F' into its respective base10 integer
int CharToInt(char c) {
    if (c <= '9') {
        return (c - '0');
    } else if (c <= 'F') {
        return (c - 'A' + 10);
    } else // c == '-' or unknown
    {
        return 0;
    }
}

// Helper function to convert an int from 0 to 15 to its char representation
char IntToChar(int x) {
    if (x < 10) // char from '0'-'9'
        return '0' + x;
    else if (x < 16)
        return 'A' + x - 10;
    else // unknown char
        return -1;
}

string ConvertBase(const string &num_as_string, int b1, int b2) {
    int base10Val = 0;
    bool isNegative = false; // check if negative
    if (num_as_string[0] == '-') isNegative = true;

    if (b1 != 10) // if not already in base 10
    {
        // multiply out the number
        // Example: 573base8.
        // Take (3 * 8^0) + (7 * 8^1) + (5 * 8^2)

        // I would also need to handle bases greater than 10, so like 5A49F
        int currentBase = 1;
        for (int i = num_as_string.size() - 1; isNegative ? i > 0: i > -1; i--) // start from back to front
        {                                                  // stopping point depends on whether string has a '-'
            base10Val += CharToInt(num_as_string[i]) * currentBase;
            currentBase *= b1;
        }
    } else { // already in base 10;
        base10Val = abs(std::stoi(num_as_string)); // just use stoi
    }

    // Convert from base10 to any base using % b2
    // Use the strategy from Ex6.1 about forming string backwards.
    string retVal;
    do {
        retVal += IntToChar(base10Val % b2);
        base10Val /= b2;
    } while (base10Val);

    // append the '-'
    retVal += isNegative ? "-" : "";

    return {rbegin(retVal), rend(retVal)};
}

/*
 * Results of MY implementation:
 * Average running time:    2 us
 * Median running time:    <1 us
 * You've passed ALL tests. Congratulations! ***
 *
 * The knowledge and methods behind my implementation are from CSS 422 Hardware
 */

/*
 * The above is my solution to the problem. I work through it like I would on paper,
 * converting from base b1 to base 10 if the number isn't already, then converting to base b2.
 */
int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
    return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                           &ConvertBase, DefaultComparator{}, param_names);
}
