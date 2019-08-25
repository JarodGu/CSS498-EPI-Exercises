#include <memory>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

/*
 * Exercise 14.1 - Test if a Binary Tree Satisfies the BST Property
 * Write a program that takes as input a binary tree and returns whether
 * it satisfies the BST property. For each node, the elements in its left
 * subtree must be less than or equal to the node. Everything in the right
 * subtree must be greater than the node.
 *
 * Initial Thoughts:
 * I might need to start from the top and move down using recursion
 * Steps:
 * 1. Check node's value
 * 2. See if it's greater than/equal to the left value
 * 3. See if it's less than the right value
 * 4. Return traverse left && traverse right
 */

/*
 * Helper function following the intial thoughts implementation.
 */
/*
bool IsBinaryTreeBSTHelper(const unique_ptr<BinaryTreeNode<int>> &root)
{
    if(root == nullptr) return true;
    if((root->left != nullptr && root->left->data > root->data)
        || (root->right != nullptr && root->right->data >= root->data))
    {
        return false;
    }
    return IsBinaryTreeBSTHelper(root->left) && IsBinaryTreeBSTHelper(root->right);
}
 */
bool IsBinaryTreeBSTHelper(const unique_ptr<BinaryTreeNode<int>> &root,
        int lowRange, int highRange)
{
    if(root == nullptr)
    {
        return true;
    }
    else if(root->data < lowRange || root->data > highRange)
    {
        return false;
    }
    return IsBinaryTreeBSTHelper(root->left, lowRange, root->data)
        && IsBinaryTreeBSTHelper(root->right, root->data, highRange);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return IsBinaryTreeBSTHelper(tree, std::numeric_limits<int>::min(),
          std::numeric_limits<int>::max());
}

/*
 * Conclusion:
 * 2910/3136 Tests passed
 * My first approach did not take into account the possible range
 * that a value may fall into. It simply checks if the immediate node's left
 * and right values satisfy the BST. Thus I would need to pass down a low
 * to high range and compare it with that as well.
 *
 * Revised Solution Results:
 * All tests passed!
 * Average running time:    3 us
 * Median running time:     3 us
 */

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
