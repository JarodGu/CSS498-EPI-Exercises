#include <string>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"

using std::string;
using std::vector;
using std::unordered_map;

/*
 * Exercise 12.5 - Find the Nearest Repeated Entries in An Array
 * People do not like reading text in which a word is used multiple
 * times in a short paragraph. Write a program that takes
 * as input an array and finds the distance between
 * a closest pair of equal entries.
 *
 * Initial Thoughts:
 * A brute force approach to have two nested for loops. The first loop
 * iterates through each word in the paragraph, and the second nested
 * loop iterates through all words again to find the distance of the
 * nearest adjacent like word. If the distance is shorter, then update it.
 * Complexity would of O(n^2).
 */

int FindNearestRepetition(const vector<string> &paragraph)
{
    // Unordered map of words and the latest index we've seen them at while iterating through
    unordered_map<string, int> wordToLatestIndex;
    // maintain a nearest repeated distance value
    int nearestRepeatedDistance = std::numeric_limits<int>::max();
    for(int i=0; i<size(paragraph); ++i)
    {
        // Find word in hash map
        if(auto latestEqualWord = wordToLatestIndex.find(paragraph[i]);
            latestEqualWord != end(wordToLatestIndex)) // If not found, returns iterator to end of hash map
        {
            // Update nearest repeated distance if the distance to the same word is less than the current
            // minimum distance.
            nearestRepeatedDistance = std::min(nearestRepeatedDistance, i - latestEqualWord->second);
        }
        // Since we've found the word again, update its found index.
        wordToLatestIndex[paragraph[i]] = i;
    }
    return nearestRepeatedDistance != std::numeric_limits<int>::max()
            ? nearestRepeatedDistance: -1;
}
/*
 * Conclusion:
 * The problem makes use of a hash map to solve the problem so we only need
 * to make a single pass over the paragraph. When a word is found, store the index
 * corresponding to that word in the hash map. Now when we encounter the word again,
 * check the hash map and see if the distance between the indices is LESS than
 * the current lowest. Then update the distance.
 *
 * Results:
 * All tests passed!
 * Average running time:   89 us
 * Median running time:    60 us
 */

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"paragraph"};
    return GenericTestMain(args, "nearest_repeated_entries.cc",
                           "nearest_repeated_entries.tsv", &FindNearestRepetition,
                           DefaultComparator{}, param_names);
}
