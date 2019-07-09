#include <string>
#include "test_framework/generic_test.h"

using std::string;
using namespace std;

/*
 * This exercise is part of the Chapter 6 Strings bootcamp.
 * Create a function that tells if a string is a palindrome.
 * 
 * Initial Thoughts:
 * Traverse the array from the front and back to the midpoint.
 * If a character does not match, then return false.
 * In my implementation, I would have set a mid-point and two variables to
 * track the beginning the end indices, then increment/decrement towards the
 * center.
 * 
 * After looking at the book, I can cleverly use the indices to 
 * know when to stop the loop AND deal with even/odd cases.
 */
bool IsPalindrome(const string &s) {
    for(int i=0, j=( s.size()-1 ); i<j; i--, j++) // the i<j means the loop ends once they converge to midpoint
    {
        if(s[i] != s[0])
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"s"};
    return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                           "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                           DefaultComparator{}, param_names);
}
