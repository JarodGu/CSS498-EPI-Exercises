#include <iterator>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"

using std::string;
using std::vector;

/*
 * Exercise 6.4 - Replace and Remove
 * We're given a char array of a specified size and need to
 * replace all the 'a's with 2 'd's and remove all 'b's.
 * Assume the char array can always hold the end result
 *
 * Initial Thoughts:
 * It would be easy to implement using library insert and delete methods, but it
 * would be horrible inefficient. One approach could be to pass through and count the
 * number of a's and b's for something (idk what).
 * It would also be possible to work from the back of the array to the front.
 *
 * Day 2 Thoughts:
 * 2 cycles O(2n) = O(n) complexity
 * First cycle replaces 'b's with '' and counts the 'a's
 * Second cycle works backwards and inserts the 'a's
 */
int ReplaceAndRemove(int size, char s[]) {
    /*
    // Cycle 1: Count 'a's and delete 'b's
    int newSize = size;
    for(int i=0; i<size; i++)
    {
        if(s[i] == 'a')
        {
            newSize += 2;
        }
        else if(s[i] == 'b') // when deleting the 'b's I'm not just replacing it with ''
        {                   // and instead replacing it with the character 1 ahead.
            s[i] = s[i+1];
            --newSize;
        }
    }

    // Cycle 2: Work backwards and replace 'a's with 'd''d's
    // Will need to track two indices:
            // Index of character observed -> size
            // Index of point to start replacing -> newSize
    // For example, if I'm looking forward and see an 'a' at i1, then I put 'd''d' at i2 and i2-1
    const int FINAL_SIZE = newSize;
    while(newSize)
    {
        if(s[--size] == 'a')
        {
            s[--newSize] = 'd';
            s[--newSize] = 'd';
        }
        else // Any other character
        {
            --newSize;
        }
    }
    return FINAL_SIZE;
     */

    // Cycle 1: Count 'a's and delete 'b's
    int writeIndex = 0, aCount = 0;

    for(int i=0; i<size; i++)
    {
        if(s[i] != 'b')
        {
            s[writeIndex++] = s[i];
        }
        if(s[i] == 'a')
        {
            ++aCount;
        }
    }

    // Cycle 2: Work backwards and replace 'a's with 'd''d's starting from end
    int currentIndex = writeIndex - 1;
    writeIndex = writeIndex + aCount - 1;
    const int FINAL_SIZE = writeIndex + 1;

    while(currentIndex >= 0)
    {
        if(s[currentIndex] == 'a')
        {
            s[writeIndex--] = 'd';
            s[writeIndex--] = 'd';
        }
        else // Any other character
        {
            s[writeIndex--] = s[currentIndex];
        }
        --currentIndex;
    }
    return FINAL_SIZE;
}

// Included test code
vector<string> ReplaceAndRemoveWrapper(TimedExecutor &executor, int size,
                                       const vector<string> &s) {
    std::vector<char> s_copy(s.size(), '\0');
    for (int i = 0; i < s.size(); ++i) {
        if (!s[i].empty()) {
            s_copy[i] = s[i][0];
        }
    }

    int res_size =
            executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

    vector<string> result;
    for (int i = 0; i < res_size; ++i) {
        result.emplace_back(string(1, s_copy[i]));
    }
    return result;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "size", "s"};
    return GenericTestMain(args, "replace_and_remove.cc",
                           "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                           DefaultComparator{}, param_names);
}
