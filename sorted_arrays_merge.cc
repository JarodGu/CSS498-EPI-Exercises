#include <vector>
#include "test_framework/generic_test.h"

using std::vector;

/*
 * Exercise 10.1 - Merge Sorted Files
 * A set of sequences containing numbers each have elements
 * that are already sorted. Merge these into one larger sorted
 * array.
 *
 * Initial Thoughts:
 * I would need x indexes the current position in each sorted array.
 * Maybe I can use iterators (a list of iterators).
 * Compare each iterator's position's value and add the smallest
 * to the return array and increment the iterator. I can also
 * take advantage of a min-heap.
 *
 * How would I declare an iterator for a vector?
 */

/*
 * My attempt:
 *
vector<int> MergeSortedArrays(const vector<vector<int>> &sorted_arrays) {

    // Vector holds the current index for each respective array
    vector<int> minIndices(3, sorted_arrays.size());

    int retValIndex;
    vector<int> retVal;

    // How to tell I've reached the end?
    // I don't want to iterate through everything to get the sum... unecessary
    // Not sure how to do it without though...

    // Compute return vector size
    int maxSize = 0;
    for(int i=0; i<minIndices.size(); i++)
    {
        maxSize += sorted_arrays[i].size();
    }

    // Select which element to add and increase that index.
    for(int i=0; i<maxSize; i++)
    {
        int minIndex = -1;
        int minElement = INT_MAX;
        for(int j=0; j<minIndices.size(); j++) // Cycle through all valid sorted_arrays
        {
            if(minIndices[j] < sorted_arrays[j].size()) { // Skip completed arrays
                if (sorted_arrays[j][minIndices[j]] < minElement) {
                    // Update max element
                    // Update max index
                    minElement = sorted_arrays[j][minIndices[j]];
                    minIndex = j;
                    // Increment index tracker
                    minIndices[j]++;
                }
            }
        }
        retVal.push_back(minElement);
    }
    return retVal;
}
*/
/*
 * Conclusion:
 * It seemed like an easy problem but I still referred to the book.
 * I wanted to see how they would use a heap to solve it.
 * The below solution uses a struct to hold the beginning
 * and end indices of each sorted array.
 *
 * A min heap is built, then deconstructed by popping off the top
 * element onto the return merged array.
 *
 * Results:
 * All tests passed!
 * Average running time:  447 us
 * Median running time:    <1 us
 *
 * Complexity:
 * Time complexity is O(n log k)
 *      where n is the number of elements
 *      and k the number of sorted arrays
 * Space complexity is O(k) + space needed for the final merged result
 */
struct IteratorCurrentAndEnd
{
    bool operator>(const IteratorCurrentAndEnd& that) const{
        return *current > *that.current;
    }
    vector<int>::const_iterator current;
    vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int>> &sorted_arrays)
{
    std::priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd>, std::greater<>>
    minHeap;

    // Sorted array contains n elements where
    // n is the number of lists in sorted_arrays.
    // It's just loading the first element in each provided onto the min heap.
    for(const vector<int> &sorted_array : sorted_arrays)
    {
        if(!sorted_array.empty()) // if sorted array isn't empty
        {
            minHeap.emplace(IteratorCurrentAndEnd{sorted_array.cbegin(), sorted_array.cend()});
        }
    } // At this step, a min heap is built with the first element in each sorted array

    // Declare return array
    vector<int> retVal;

    while(!minHeap.empty())
    {
        // We want to pop off the smallest element in the min heap, which
        // is minHeap.top(), and push it into our return vector.
        IteratorCurrentAndEnd smallest_array = minHeap.top();
        minHeap.pop();
        retVal.push_back(*smallest_array.current);

        // Now if the sorted_array isn't at the end, push the next value
        // in line onto the heap
        if(std::next(smallest_array.current) != smallest_array.end)
        {
            minHeap.push(IteratorCurrentAndEnd{
                std::next(smallest_array.current), smallest_array.end});
        }
    }
    return retVal;
}


int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"sorted_arrays"};
    return GenericTestMain(args, "sorted_arrays_merge.cc",
                           "sorted_arrays_merge.tsv", &MergeSortedArrays,
                           DefaultComparator{}, param_names);
}
