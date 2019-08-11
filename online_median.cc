#include <vector>
#include <queue>
#include "test_framework/generic_test.h"

using std::vector;
using std::priority_queue;

/*
 * Exercise 10.5 - Compute the Median of Online Data
 * Data is given in a stream fashion. You cannot back up to read an
 * earlier value and you need to output the median after reading
 * in each new element. Design an algorithm for computing the
 * running median of a sequence.
 *
 * Initial Thoughts:
 * Say the average of three elements is A. I've stored A into
 * slot [2]. The next value is 5. To calculate the average for slot [3],
 * I would take A, add 5, then divide by the n=4.
 *
 * Might need to make a function that returns this value.
 */

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator &sequence_end) {
    /*
    int sum = 0;
    vector<double> retVal;
    for (int n = 1; sequence_begin < sequence_end; n++, sequence_begin++) {
        // instead of maintaining an ongoing median, I just maintain the ongoing sum.
        // Not sure if this would be allowed.
        sum += *sequence_begin;
        retVal.push_back(sum / (double)n);
    }
    return retVal;
    */
    // Results:
    // My guess is that this solution wouldn't be allowed because
    // it would be like storing the stream of data.
    // Average running time:   <1 us
    // Median running time:    <1 us
    // You've passed 2/55 tests. ***

    // Referring to the book's solution

    // min heap stores the larger half seen so far
    priority_queue<int, vector<int>, std::greater<>> minHeap;
    // max heap stores the smaller half seen so far
    priority_queue<int, vector<int>, std::less<>> maxHeap;
    vector<double> retVal;

    while(sequence_begin != sequence_end)
    {
        minHeap.emplace(*sequence_begin++);
        maxHeap.emplace(minHeap.top());
        minHeap.pop();
        // Ensure min and max heaps have equal number of elements if
        // an even number of elements is read, otherwise min heap must
        // have one more element than max heap
        if(maxHeap.size() > minHeap.size())
        {
            minHeap.emplace(maxHeap.top());
            maxHeap.pop();
        }
        retVal.push_back(minHeap.size() == maxHeap.size()
            ? 0.5 * (minHeap.top() + maxHeap.top()) : minHeap.top());
    }
    return retVal;
}

/*
 * Conclusion:
 * I've realized that we want the median (ie. middle) element, not the mean...
 * This also requires that the elements read in are sorted. The min heap stores the
 * smaller half seen so far, and max heap stores the larger half seen.
 * So the result will either be the min heap's top() if it's an odd element,
 * or min heap top() + max heap top() / 2 if it's an even element.
 * The time complexity is O(log n) for insertion and extraction from a heap
 *
 * Results:
 * All tests passed
 * Average running time:    1 ms
 * Median running time:    <1 us
 */

vector<double> OnlineMedianWrapper(const vector<int> &sequence) {
    return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"sequence"};
    return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                           &OnlineMedianWrapper, DefaultComparator{},
                           param_names);
}
