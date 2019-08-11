#include <queue>
#include <vector>
#include "test_framework/generic_test.h"

using std::vector;
using std::priority_queue;

/*
 * Exercise 10.3 - Sort an Almost-Sorted Array
 * An almost sorted array has elements who are at most
 * k positions away from their final sorted position. Write a function
 * that takes a long sequence of almost sorted numbers
 * and prints the numbers in sorted order.
 *
 * Initial Thoughts:
 * A constantly shifting min heap would help solve this problem.
 * Specifically a min heap
 * would work best. Once I've read k elements ahead after the current position,
 * place the minimum element from the heap and pop another one on.
 */

vector<int> SortApproximatelySortedData(
        vector<int>::const_iterator sequence_begin,
        const vector<int>::const_iterator &sequence_end, int k) {
    // This declares a min heap instead of the default max heap
    priority_queue<int, vector<int>, std::greater<>> minHeap;
    vector<int> retVal;

    // Use the provided iterators
    while(sequence_begin != sequence_end)
    {
        minHeap.push(*sequence_begin++); // Push current value onto heap
        if(minHeap.size() > k + 1)
        {
            retVal.push_back(minHeap.top());
            minHeap.pop();
        }
    }
    // Pop any remaining elements
    while(!minHeap.empty())
    {
        retVal.push_back(minHeap.top());
        minHeap.pop();
    }

    return retVal;
}

/*
 * Conclusion:
 * Managed to solve this one by only referring to the book's hint.
 * Working it out on the white board helped identify a way to solve it.
 * Say we're at index i. Once we've reached index i + k, the element at the top
 * of the min heap gets popped off into the return array. The trick
 * was declaring the min heap properly by using the greater<> comparison.
 *
 * Results:
 * All tests PASSED
 * Average running time:  128 us
 * Median running time:    <1 us
 */

vector<int> SortApproximatelySortedDataWrapper(const vector<int> &sequence,
                                               int k) {
    return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"sequence", "k"};
    return GenericTestMain(
            args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
            &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
