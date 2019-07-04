#include <vector>
#include <array>
#include "test_framework/generic_test.h"
using std::vector;
using std::array;
/*
 * The spiral order of a 2D array starts from [0][0] then moves in a
 * cycle of right, down, left, up until it reaches the center. It cannot
 * pass over the same element twice.
 *
 * NOTE: C++ is row-major, so [a][b] means "a" addresses a row and "b" a column
 *
 * Initial Thoughts:
 * I can maintain a direction variable to keep track of which direction I'm moving.
 * I'll also need a row/col index to track my current position in the 2D array.
 * Start from [0][0] and move right until reaching the rightStop stopping point,
 * then change directions.
 * Keep doing this until all elements in the 2D array are traversed
 */

vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
  /*
  vector<vector<int>> &arr = square_matrix;
  int rightStop, botStop, leftStop, topStop; // Maintain variables for the boundaries of where to stop and change directions
  rightStop = arr.size() - 1;
  botStop = arr.size() - 1;
  leftStop = 0;
  topStop = 1;

  vector<int> retVal; // the return value

  int row = 0, col = 0; // track current position

  // Traverse until the stopping point is reached, then change directions
  int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up
  for(int i=0; i< arr.size() * arr.size(); i++)
  {
      // change a stopping point once reached
      // One if case for each direction
            // Then a nested if case to see if it's at the end.
      if(direction == 3) // Moving up
      {
          if(row > topStop)
          {
              retVal.push_back(arr[row--][col]);
          } else {
              retVal.push_back(arr[row][col++]);
              topStop++;
              direction = 0; // cycle complete
          }
      }
      else if(direction == 2) // Moving left
      {
          if(col > leftStop)
          {
              retVal.push_back(arr[row][col--]);
          } else { // Stop reached
              retVal.push_back(arr[row--][col]);
              leftStop++;
              direction = 3;
          }
      }
      else if(direction == 1) // Moving down
      {
          if(row < botStop)
          {
              retVal.push_back(arr[row++][col]);
          } else { // Stop reached
              retVal.push_back( arr[row][col--]);
              botStop--;
              direction = 2;
          }
      }
      else if(direction == 0) // Moving right
      {
          if(col < rightStop)
          {
            // Add to spiral ordering and increment col index
            retVal.push_back( arr[row][col++] );
          } else { // Stop reached
            // Switch direction to down and decrement the rightStop
            retVal.push_back( arr[row++][col]);
            rightStop--;
            direction = 1;
          }
      }
  }
  return retVal;
  */

   /*
    *   Results: Average running time:   58 us
    *   Median running time:    <1 us
    *
   * The above is MY solution without referring to the book and it PASSED all tests!
   * It was also a similar methodology to the answer in the book.
   * The below function is the version that uses only one if statement.
   * Both have a time complexity of O(n^2) where n is a size of the n*n 2D array
   * and a space complexity of O(1)
   */
    const array<array<int, 2>, 4> kShift = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
    // The kShift const array is added on to change the current [row][col] index
    int dir = 0, x = 0, y = 0;
    vector<int> spiral_ordering;

    for (int i = 0; i < square_matrix.size() * square_matrix.size(); ++i) {
        spiral_ordering.emplace_back(square_matrix[x][y]);
        square_matrix[x][y] = 0;
        int next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];
        if (next_x < 0 || next_x >= square_matrix.size() || next_y < 0 ||
            next_y >= square_matrix.size() || square_matrix[next_x][next_y] == 0) {
            dir = (dir + 1) % 4;
            next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];
        }
        x = next_x, y = next_y;
    }
    return spiral_ordering;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering_segments.cc",
                         "spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
                         DefaultComparator{}, param_names);
}
