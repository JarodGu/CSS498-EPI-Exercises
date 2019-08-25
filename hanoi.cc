#include <array>
#include <stack>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::array;
using std::stack;
using std::vector;
const int kNumPegs = 3;

/*
 * Exercise 15.1 - The Towers of Hanoi Problem
 * A peg contains a stack of rings sorted from largest at the bottom to
 * smallest at the top and must be transferred to another empty peg. We are given
 * 2 empty pegs to work with.
 *
 * Initial Thoughts:
 * I'm confused as to how to go about this problem.
 */
/*
 * Recursive helper function
 */
void ComputeTowerHanoiSteps(int numRingsToMove, array<stack<int>, kNumPegs> &pegs,
        int fromPeg, int toPeg, int usePeg,
        vector<vector<int>> *retVal)
{
    // Attempting to describe what each step does.
    if(numRingsToMove > 0)
    {
        ComputeTowerHanoiSteps(numRingsToMove - 1, pegs, fromPeg, usePeg, toPeg, retVal);
        pegs[toPeg].push(pegs[fromPeg].top());
        pegs[fromPeg].pop();
        retVal->emplace_back(vector<int>{fromPeg, toPeg});
        ComputeTowerHanoiSteps(numRingsToMove - 1, pegs, usePeg, toPeg, fromPeg, retVal);
    }
}

// Driver function
vector<vector<int>> ComputeTowerHanoi(int num_rings)
{
    array<stack<int>, kNumPegs> pegs;
    // Initialize pegs
    for(int i=num_rings; i >= 1; --i)
    {
        pegs[0].push(i);
    }
    vector<vector<int>> retVal;
    ComputeTowerHanoiSteps(num_rings, pegs, 0, 1, 2, &retVal);
    return retVal;
}

/*
 * Conclusion:
 * This problem was difficult and does recursive steps. The idea
 * is as follows:
 * If there are 3 rings that need to be moved, move 2 rings
 * to another peg and place the last ring onto the other peg.
 * Time complexity is O(2^n)
 *
 * Results:
 * All tests passed
 * Average running time:  138 us
 * Median running time:    57 us
 */

void ComputeTowerHanoiWrapper(TimedExecutor &executor, int num_rings)
{
    array<stack<int>, kNumPegs> pegs;
    for (int i = num_rings; i >= 1; --i)
    {
        pegs[0].push(i);
    }

    vector<vector<int>> result =
            executor.Run([&]
                         { return ComputeTowerHanoi(num_rings); });

    for (const vector<int> &operation : result)
    {
        int from_peg = operation[0], to_peg = operation[1];
        if (!pegs[to_peg].empty() && pegs[from_peg].top() >= pegs[to_peg].top())
        {
            throw TestFailure("Illegal move from " +
                              std::to_string(pegs[from_peg].top()) + " to " +
                              std::to_string(pegs[to_peg].top()));
        }
        pegs[to_peg].push(pegs[from_peg].top());
        pegs[from_peg].pop();
    }
    array<stack<int>, kNumPegs> expected_pegs1, expected_pegs2;
    for (int i = num_rings; i >= 1; --i)
    {
        expected_pegs1[1].push(i);
    }
    for (int i = num_rings; i >= 1; --i)
    {
        expected_pegs2[2].push(i);
    }
    if (pegs != expected_pegs1 && pegs != expected_pegs2)
    {
        throw TestFailure("Pegs doesn't place in the right configuration");
    }
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "num_rings"};
    return GenericTestMain(args, "hanoi.cc", "hanoi.tsv",
                           &ComputeTowerHanoiWrapper, DefaultComparator{},
                           param_names);
}
