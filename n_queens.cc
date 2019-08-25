#include <algorithm>
#include <iterator>
#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using std::make_unique;
/*
 * Exercise 15.3 - Generate All Non-Attacking Placements of n-Queens
 * A non-attacking placement of queens is one where no two queens are in the same row,
 * column, or diagonal. Write a program that returns all distinct non-attacking placements
 * of n queens on an n x n chessboard, where n is an integer input.
 *
 * Initial Thoughts:
 * The book provides a picture of a configuration for 4 queens.
 * On a 4x4 chessboard, these are their positions:
 * Config 1: <1, 0>, <3, 1>, <0, 2>, <2, 3>
 * Config 2: <2, 0>, <0, 1>, <3, 2>, <1, 3>
 *
 * There's a queen on every row and column. Their pattern is
 * shaped like a square placed at a 30 degree angle.
 */
/*
 * Helper function to determine if placing a queen wouldn't conflict
 * in placement with the other queens. Checks for horizontal, vertical,
 * and diagonal alignment to other queens.
 */
bool IsValid(const vector<int> &colPlacement)
{
    int rowID = size(colPlacement) -1;
    for(int i=0; i < rowID; ++i)
    {
        if(int diff = abs(colPlacement[i] - colPlacement[rowID]);
            diff == 0 || diff == rowID - i)
        {
            // A column or diagonal constraint is violated
            return false;
        }
    }
    return true;
}

/*
 * Recursive function to go through each row/column
 * and build a solution containing the placement of all queens.
 */
void SolveNQueens(int n, int row, vector<int>* colPlacement,
        vector<vector<int>>* retVal)
{
    if(row == n)
    {
        // All queens are legally placed
        retVal->emplace_back(*colPlacement);
    } else {
        for(int col = 0; col < n; col++)
        {
            colPlacement->emplace_back(col);
            if(IsValid(*colPlacement))
            {
                SolveNQueens(n, row + 1, colPlacement, retVal);
            }
            colPlacement->pop_back();
        }
    }
}

// Driver function
vector<vector<int>> NQueens(int n) {
  vector<vector<int>> retVal;
  SolveNQueens(n, 0, make_unique<vector<int>>().get(), &retVal);
  return retVal;
}

/*
 * Conclusion:
 * The brute force solution would be to test every possible queen location
 * for all spots on the board. Complexity grows immensely as n increases.
 * The solution is to have an IsValid function to check whether
 * a queen can be placed at a specific coordinate. It compares the location
 * with all previously placed queens.
 *
 * Results:
 * All tests passed:
 * Average running time:    5 ms
 * Median running time:    78 us
 */

bool Comp(vector<vector<int>>& a, vector<vector<int>>& b) {
  std::sort(std::begin(a), std::end(a));
  std::sort(std::begin(b), std::end(b));
  return a == b;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens, &Comp,
                         param_names);
}
