#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"

using std::string;

/*
 * Exercise 6.1 - Interconvert Strings and Integers
 * Create two functions to convert a string to an integer
 * and vice versa. Cannot use stoi/atoi.
 *
 * Initial Thoughts:
 * The number 573 is also 500 + 70 + 3. Each decimal place
 * is represented by 10^x where x is the place.
 * When going from string to integer, I can add (digit)*10^x for each digit to
 * get the integer.
 *
 * Now going from integer to string seems more difficult. I can create a switch with digits 0-9
 * and add to a string depending on each digit. I can take the integer mod 10 to extract single digits then
 * add them to the return string.
 */

/*
 * Function converts an integer to a string without stoi/atoi
 * I used the solution in the book for this one. They take into
 * account how expensive adding to the beginning of a string is,
 * since you need to shift everything over. In this solution, we form the string backwards
 * so the x=-577 would form as "775-", then return the backwards iteration of "-577"
 */
string IntToString(int x) {
    // Check if integer is negative
    bool isNegative = false;
    if(x<0)
    {
        isNegative = true;
    }

    string retVal = ""; // return string

    // doWhile is the perfect type of loop for this case because we do
    // not know how big the integer is, thus we keep dividing it
    // by 10. We also execute it at least once in case the integer is 0.
    do
    {
        retVal += '0' + abs(x % 10); // Manually add the zero in case int x is literally 0.
                                    // abs(x%10) adds digits from MSB->LSB
        x /= 10;
    } while (x);

    // Now add the negative back
    retVal += isNegative ? "-" : ""; // like a simple operation if/else
    return { rbegin(retVal), rend(retVal) }; //creates a string from back to front
                                            // This is because one way to make a string is to use
                                            // a pair of iterators. rbegin is a reverse iterator going
                                            // from back to front and rend is the stopping point, pointing
                                            // to the character BEFORE the first char in retVal (ie nothing)
                                            // The string created contains all characters from [begining,end)
}

// Helper function to decode a digit
int DecodeCharToInt(const char c)
{
    switch (c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return -1;
    }
}

/*
 * Function converts a string to an integer WITHOUT stoi/atoi
 */
int StringToInt(const string &s) {
    // My implementation. Uses a helper function to decode the digits.
    /*
    int retVal = 0;
    int multiplier = 1; // multiply by 10 when incrementing to next digit
    for(int i=s.size()-1; i>-1; i--) // end to front
    {
        if(s[i] == '-')
        {
            retVal *= -1; // Make the product negative
        }
        else // character is a digit
        {
            retVal += DecodeCharToInt(s[i])*multiplier;
            multiplier *= 10;
        }
    }
    return retVal;
     */
    //---------------------------------------
    // Now for the books single line implementation
    return (s[0] == '-' ? -1 : 1) // this line determines whether the answer's negative
            * accumulate(begin(s) + (s[0] == '-'), end(s), 0, [](int running_sum, char c) // I have no idea what this does
            {
                return running_sum * 10 + c - '0';
            });
}

/*
 * My implementation:
 * Results: All tests PASSED
 * Average Running time: 2 us
 * Median Running time: <1 us
 * -------------------------
 * Book's implementation:
 * Average running time:    2 us
 * Median running time:    <1 us
 */

void Wrapper(int x, const string &s) {
    if (IntToString(x) != s) {
        throw TestFailure("Int to string conversion failed");
    }

    if (StringToInt(s) != x) {
        throw TestFailure("String to int conversion failed");
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "s"};
    return GenericTestMain(args, "string_integer_interconversion.cc",
                           "string_integer_interconversion.tsv", &Wrapper,
                           DefaultComparator{}, param_names);
}
