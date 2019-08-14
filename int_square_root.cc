#include "test_framework/generic_test.h"

/*
 * Exercise 11.4 - Compute the Integer Square Root
 * Write a program which takes a nonnegative integer and returns
 * the largest integer whose square is less than or equal to the given integer.
 * For example, if the integer is 16 return 4. If it's 300, return 17
 * since 17^2 = 289 < 300 and 18^2 = 324 > 300.
 *
 * Initial Thoughts:
 * I'm hoping the proper solution doesn't make use of hashmaps
 * since I'm not too experience with those.
 * Maybe I can make use of STL's sqrt function.
 *
 * After researching, binary search can also be used to find the sqrt of an integer.
 * The algorithm is as follows:
 * 1. Start with 'start = 0' and 'end = x'
 * 2. while(start <= end)
 *      a) Compute 'mid' as (start + end)/2
 *      b) Compare mid*mid with x
 *      c) If x == mid*mid, return mid
 *      d) If x is greater, binary search between mid+1 and the end
 *      e) If x is smaller, do binary search between start and mid
 */
int SquareRoot(int k) {

/*
    // My solution from https://www.geeksforgeeks.org/square-root-of-an-integer/
    if(k == 0 || k == 1) return k;

    int start = 1, end = k, retVal;
    while (start <= end)
    {
        long long mid = start + (end - start) / 2; //(start + end) / 2;

        // If k is a perfect square
        if (mid * mid == k) {
            return mid;
        }

        // Since using a floor, update answer when mid*mid is
        // smaller than k, and move closer to sqrt(x)
        if (mid * mid < k)
        {
            start = mid + 1;
            retVal = mid;
        } else // If mid*mid is greater than x
        {
            end = mid - 1;
        }
    }
    return retVal;
*/
    // Book's solution
    int left = 0, right = k;
    // Candidate interval [left, right] where everything before left has
    // square <= k, and everything after has square > k
    while(left <= right)
    {
        long long mid = left + ((right - left) / 2);
        if(long long mid_squared = mid * mid; mid_squared <= k)
        {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left - 1;

}

/*
 * My Solution Results:
 * Average running time:    2 us
 * Median running time:    <1 us
 *
 * Book's Solution Results:
 * Average running time:   <1 us
 * Median running time:    <1 us
 *
 * Conclusion:
 * I did not expect the problem would make use of binary search to solve
 * the problem. I haven't had much experience using binary search, but it
 * makes sense in this case. To summarize, the interval from [left, right]
 * are the possible candidates that when squared, would produce the correct answer.
 *
 * Binary search is used to narrow the results after every iteration. If the mid
 * point between left and right squared is LESS than k, then we update
 * left to equal the mid point + 1. It means all points to the left when squared
 * are less than k.
 * If the mid point squared is GREATER than k, then we update right
 * to equal mid - 1. All points to the right when squared
 * are greater than k.
 *
 * Binary search works because it's like searching an array of incrementing integers.
 * Instead of the integer's value determining the candidate interval, we base
 * it on the integer^2.
 */
int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"k"};
    return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                           &SquareRoot, DefaultComparator{}, param_names);
}
