#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

/*
 * Exercise 9.2 - Test if Binary Tree is Symmetrical
 * A tree is symmetrical if when folded across the root, all elements
 * have the same value and structure. Write a function that returns
 * whether a binary tree is symmetrical.
 *
 * Initial Thoughts:
 * Would I be able to do recursion to solve this problem? Whenever
 * I traverse left, another pointer traverses right. Maybe I can use
 * a recursive function that takes two pointers, which traverses in tandem.
 * Once a mismatch is found, return false.
 *
 * Wondering how the call stack would return
 */

/*
 * Helper function used to traverse the tree in tandem to test
 * each node for symmetry.
 */
bool SymmetricHelper(const unique_ptr<BinaryTreeNode<int>> &pLeft,
                     const unique_ptr<BinaryTreeNode<int>> &pRight) {
    if(pLeft && pRight != nullptr)
    {
        if(pLeft->data == pRight->data) {
            // Left node's traversal: Node, Left, Right
            // Right node's traversal: Node, Right, Left
            return SymmetricHelper(pLeft->left, pRight->right)
            & SymmetricHelper(pLeft->right, pRight->left);
        }
        return false;
    }
    // Either 1 or both null
    return (pLeft == nullptr && pRight == nullptr);
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>> &tree) {
    /*
    if (tree != nullptr) {
        auto *pLeft = tree->left.get();
        auto *pRight = tree->right.get();
        return SymmetricHelper(pLeft, pRight);
    }
    return true; // Tree is empty, thus symmetric
     */
    return tree == nullptr || SymmetricHelper(tree->left, tree->right);
}

/*
 * Conclusion:
 * My solution to the proble worked! This is the first problem in
 * a while that I've been able to complete without referring to the book.
 * Solid understanding of binary trees from 342 and 343 helped. Optimized
 * my code using techniques from the book's solution.
 *
 * Results:
 * *** You've passed ALL tests. Congratulations! ***
 * Average running time:   <1 us
 * Median running time:    <1 us
 *
 * Time complexity is O(n) and space complexity O(h)
 * where n is the number of nodes in the tree, and h the height of the tree
 */

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree"};
    return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                           &IsSymmetric, DefaultComparator{}, param_names);
}
