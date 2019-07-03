#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <random>



#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::vector;

/*
 * When testing a new website design, it's important to first roll it out to
 * only a small set of clients to receive feedback instead of pushing it
 * out to the entire client base.
 *
 * Create a function that selects a random subset of size k from the
 * entire customer base. Return the result in the input array.
 * ---------
 * Initial Thoughts:
 * I need to select a random set of clients from the array and store it in
 * the input array itself. I may also need to resize the array to k.
 *
 * Each element needs a chance to be included though. This means I can't just
 * start from the beginning and select random elements. Where I start has to be
 * random (ie quicksort/pivot). Maybe I select a pivot and expand from it. This
 * would work, but I would need to allocate an additional array to store
 * the selected candidates.
 *
 * ----------
 * After referring to the book, the best approach is the maintain a subarray at
 * the start of the input array and grow it.
 * Steps:
 * Search for random element from [0,4] and swap to index 0
 * Search for random element from [1,4] and swap to index 1
 * Search for random element from [2,4] and swap to index 2
 *
 * We've now created a random subset of size 3. It uses a seed
 * to generate the random number.
 */
void RandomSampling(int k, vector<int>* A_ptr) {
  // TODO - you fill in here.
  vector<int> &arr = *A_ptr;

  for(int i=0; i<k; i++)
  {
      // Generate random index from [i, arr.size() - 1]
      int randomIndex = rand() % (arr.size() - i) + i;
      std::swap(arr[randomIndex], arr[i]); // swap so from [0,k] is the random subset of size k
  }

  // The time complexity is O(k) because for each element in the array, we have to
  // pick a random element.
  // Space complexity is O(1)
}

bool RandomSamplingRunner(TimedExecutor& executor, int k, vector<int> A) {
  vector<vector<int>> results;

  executor.Run([&] {
    for (int i = 0; i < 100000; ++i) {
      RandomSampling(k, &A);
      results.emplace_back(begin(A), begin(A) + k);
    }
  });

  int total_possible_outcomes = BinomialCoefficient(A.size(), k);
  sort(begin(A), end(A));
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(A.size(), k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, A.size(), k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSamplingWrapper(TimedExecutor& executor, int k,
                           const vector<int>& A) {
  RunFuncWithRetries(
      bind(RandomSamplingRunner, std::ref(executor), k, std::cref(A)));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "k", "A"};
  return GenericTestMain(args, "offline_sampling.cc", "offline_sampling.tsv",
                         &RandomSamplingWrapper, DefaultComparator{},
                         param_names);
}
