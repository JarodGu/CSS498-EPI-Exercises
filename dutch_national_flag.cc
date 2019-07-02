#include <array>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
typedef enum { kRed, kWhite, kBlue } Color;

/*
 * Dutch flag partitioning is used to enhance a quicksort algorithm. The rules
 * are as follows:
 *      Elements less than a pivot index < Elements equal to pivot < Elements greater than pivot
 *
 * Implement a function that does this.
 *
 * Thoughts:
 * It seems similar to the even_odd_array problem I just did. I might need three values.
 * The easy brute force solution would be to create three lists and add values less than, equal to,
 * and greater than the pivot to each corresponding one, then piece them together in-order.
 *
 * After Referring to Book:
 * There are lots of ways to solve it without allocating more memory.
 * One of the best is to maintain 4 subarrays:
 *      LessThanPivot, EqualToPivot, GreaterThanPivot, and Unclassified
 * Goal is to shrink the Unclassified subarray and grow the others
 */

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
  // TODO - you fill in here.
  vector<Color>& arr = *A_ptr; // deref the pointer to make life easier
  Color pivot = arr[pivot_index]; // store pivot VALUE to make life easier

  // Four indices for each subarray. The equalTo index serves double duty as the unclassified's index
  int lessThan = 0, equalTo = 0, greaterThan = arr.size();

  while(equalTo < greaterThan)
  {
      // Check the unclassified
      if(arr[equalTo] < pivot) // less than pivot
      {
          std::swap(arr[equalTo++], arr[lessThan++]); // grow the subarray and swap to the unclassifieds
      }
      else if(arr[equalTo] == pivot) // equal to pivot
      {
          equalTo++; // Would just need to increment the equalTo index.
                     // This is because it will get swapped forward with the prior if/else case.
      }
      else // greater than pivot
      {
          std::swap(arr[equalTo], arr[--greaterThan]);
          // We wouldn't increment the equalTo index because unclassified subarray is
          // shrinking from the end side by decrementing the greaterThan index.
      }
  }
  // Results: Average running time 14us all tests Passed
  // The algorithm is O(n) time complexity, requiring only one pass through the array
  // with a space complexity of O(1).
}


void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[colors[i]]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
