#include <set>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

/*
 * This function from the Array's boot camp sorts an unsorted array
 * with all EVEN elements appear first. I cannot allocate additional arrays.
 *
 * After thinking it through, we have 3 sections: UNKNOWN, EVEN, and ODD.
 * The goal is to grow the EVEN section starting at index 0. We can do this
 * by swapping the first odd element we see later in the array.
 */
void EvenOdd(vector<int>* A_ptr) {

  vector<int> &arr = *A_ptr; // dereference the pointer parameter to work with the array
  /*
  for(int i=0; i<arr.size() - 1; i++) // Loop for the EVEN section. Do size - 1 since the last swap will fix it
  {
      if(arr[i] % 2 != 0) // value is odd
      {
          for(int j=i; j<arr.size(); j++) // loop to find the first even element and swap with current odd element
          {
                //...
          }
      }
  }
   */
  //My implementation is O (n*log(n)) efficient.
  //---------------------------------------------------------------
  // Now the for the book's implementation
  int next_even = 0, next_odd = arr.size() - 1;
  while(next_even < next_odd) // both the beginning and end of the array is worked on.
  {                           // when the element is even, next_even grows. if odd, swap it with
                              // whatever's element's at the end.
      if(arr[next_even] % 2 == 0)
      {
          ++next_even;
      } else {
          std::swap(arr[next_even], arr[next_odd--]);
      }
  }
  return; // complexity of this one is O(n) and space complexity is O(1)
}
void EvenOddWrapper(TimedExecutor& executor, vector<int> A) {
  std::multiset<int> before(begin(A), end(A));

  executor.Run([&] { EvenOdd(&A); });

  bool in_odd = false;
  for (int a : A) {
    if (a % 2 == 0) {
      if (in_odd) {
        throw TestFailure("Even elements appear in odd part");
      }
    } else {
      in_odd = true;
    }
  }

  std::multiset<int> after(begin(A), end(A));
  if (before != after) {
    throw TestFailure("Elements mismatch");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "even_odd_array.cc", "even_odd_array.tsv",
                         &EvenOddWrapper, DefaultComparator{}, param_names);
}
