#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <queue>

using std::unique_ptr;
using std::vector;
using std::queue;

/*
 * Exercise 8.6 - Compute Binary Tree Nodes in Order of Increasing Depth
 * Return an array of keys that contain the list of elements at that level.
 * For example, a binary tree that looks like this:
 *
 *          1
 *         / \
 *        3   67
 *
 *  Would return an array of 2 elements containing [<1>, <3, 67>]
 *
 *  Initial Thoughts:
 *  The problem is in the queue section of the book so I would likely need to make use of that.
 *  What is the best way to traverse the tree so that I can return the info?
 *
 *  I traverse it let's say using in-order traversal. If I do it iteratively it may
 *  be difficult to track what height I'm currently at.
 *
 *  I can also make a recursive function that traverses the tree
 *  and passes the current height, while adding it to the corresponding
 *  return array.
 */


/*
 * Function to traverse the binary tree in pre-order while passing info about the depth
 * and the array
 */
/*
void PreorderDepth(const unique_ptr<BinaryTreeNode<int>> &node, int depth, vector<vector<int>> &arr) {
    // Check current node and create vector for level if non-existant
    if(arr.size() <= depth)
    {
        vector<int> newLayer;
        arr.push_back(newLayer);
    }

    arr[depth].push_back(node->data);

    if (node->left != nullptr) {
        // Traverse left
        PreorderDepth(node->left, (depth+1), arr);
    }

    if (node->right != nullptr) {
        // Traverse right
        PreorderDepth(node->right, (depth+1), arr);
    }
}

vector<vector<int>> BinaryTreeDepthOrder(const unique_ptr<BinaryTreeNode<int>> &tree) {
    vector<vector<int>> retVal;

    // Check for empty tree
    if(!tree.get()) return retVal;

    PreorderDepth(tree, 0, retVal);
    return retVal;
}
*/

/*
 * RESULTS:
 * The above is my solution to the problem. It doesn't utilize queues and
 * is recursive, but made the most sense to me.
 * All tests PASSED!
 * Average running time:    8 us
 * Median running time:    <1 us
 *
 * ----------------------------------------------
 * Now for the books solution. It makes use of 2 queues
 * Average running time:   19 us
 * Median running time:    <1 us
 */

vector<vector<int>> BinaryTreeDepthOrder(const unique_ptr<BinaryTreeNode<int>> &tree) {
    vector<vector<int>> result;
    if (!tree.get()) return result;

    queue<BinaryTreeNode<int> *> curr_depth_nodes({tree.get()});
    while (!curr_depth_nodes.empty())
    {
        queue<BinaryTreeNode<int>*> next_depth_nodes;
        vector<int> this_level;
        while(!curr_depth_nodes.empty())
        {
            auto curr = curr_depth_nodes.front();
            curr_depth_nodes.pop();
            this_level.push_back(curr->data);

            if(curr->left)
            {
                next_depth_nodes.push(curr->left.get());
            }
            if(curr->right)
            {
                next_depth_nodes.push(curr->right.get());
            }
        }
        result.push_back(this_level);
        curr_depth_nodes = next_depth_nodes;
    }
    return result;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree"};
    return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                           &BinaryTreeDepthOrder, DefaultComparator{},
                           param_names);
}
