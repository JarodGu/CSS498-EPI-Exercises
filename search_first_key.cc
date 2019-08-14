#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;
using std::binary_search;

/*
 * Exercise 11.1 - Search a Sorted Array for First Occurrence of k
 * Binary search can be used on a sorted array to prevent having to search
 * half the elements. In this special case, there may be multiple
 * identical elements matching the key. Write a function that returns the
 * first occurrence of a key k.
 *
 * Initial Thoughts:
 * Binary search can already be used to find a single occurrence of k.
 * Using that algorithm (which is already available via STL), I can check
 * the previous elements until it no longer matches the key, and that
 * would be the first occurrence.
 *
 * I might be able to use the STL binary_search function with a custom
 * comparator function that tracks the index, then iterate backwards from
 * there to find the first occurrence.
 */

/*
int SearchFirstOfK(const vector<int>& A, int k) {
    int L = 0, U = A.size() - 1;
    while(L <= U)
    {
        int M = L + (U-L) / 2; // Same as (L+U)/2 but avoids overflow
        if(A[M] < k) // if element is less than the target
        {
            L = M + 1;
        }
        else if(A[M] == k)
        {
            // return M;
            // I would modify the search here to iterate backwards
            // while(M > -1 && A[M--] == k); // do nothing
            // return (M + 1);

            // We've found the first occurrence of k, now iterate backwards
            while(A[M] == k)
            {
                if(M > -1) --M;
            }
            return M + 1;
        }
        else
        {
            U = M - 1;
        }
    }
    return -1; // not found
}
*/

/*
 * Conclusion:
 * My solution works and passed all the tests. However, the book cites
 * it as the naive solution. In a worst case where all elements are
 * equal to k, the algorithm has a O(n) time complexity. This is because binary
 * search algorithm would point it to the middle index, and my
 * code would iterate it backwards to the 0 index. O(n/2) simplifies to (O/n)
 *
 * Below is the book's solution to the problem. It seems similar
 * to the binary search algorithm.
 *
 * My Results:
 * All tests Passed
 * Average running time:   <1 us
 * Median running time:    <1 us
 *
 * Book's Results:
 * Average running time:   <1 us
 * Median running time:    <1 us
 */

int SearchFirstOfK(const vector<int>& A, int k) {
    int left = 0, right = A.size() - 1, retVal = -1;
    while(left <= right)
    {
        if(int mid = left + ((right - left) / 2); A[mid] > k)
        {
            right = mid - 1;
        } else if(A[mid] == k)
        {
            retVal = mid;
            right = mid - 1;
            // Nothing to the right of mid can be the first occurence of k
        } else { // A[mid] < k
            left = mid + 1;
        }
    }
    return retVal;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
