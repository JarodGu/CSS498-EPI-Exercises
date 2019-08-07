#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

/*
 * Exercise 9.1 - Is Binary Tree Height Balanced
 * A height balanced tree means that for EVERY node in the tree,
 * the difference between the heights of the left and right subtrees
 * are at most 1. Write a function that determines whether a binary tree
 * is height balanced.
 *
 * Initial Thoughts:
 * I also covered this is CSS 343, although I don't believe I implemented
 * the algorithm. Will definitely need recursion for this one.
 * Start from the root and run IsBalancedHelper(), which checks from the left
 * and right subtrees, which checks their respective left/right subtrees, which
 * checks their respective left/subtreets... and so on. The helper function would
 * return an int for height.
 */

/*
 * Struct is passed recursively and stores info about whether it's balanced and the height
 */
struct BalancedStatusWithHeight {
    bool balanced;
    int height;
};

/*
 * Helper function to recursively check if each node in the tree
 * is balanced compared to their left/right subtrees.
 */
BalancedStatusWithHeight BalancedHelper(const unique_ptr<BinaryTreeNode<int>> &tree) {
    if (tree == nullptr) {
        return {true, -1}; // This is how to return the struct
    }

    // Traverse left. If discovered not to be balanced, return FALSE
    auto leftResult = BalancedHelper(tree->left);
    if (!leftResult.balanced) {
        // Pass the FALSE all the way to the top
        return {false, 0}; // Left subtree not balanced
    }
    // Traverse right
    auto rightResult = BalancedHelper(tree->right);
    if (!rightResult.balanced) {
        return {false, 0};
    }

    // Both left and right are balanced. Check their heights
    if(abs(rightResult.height - leftResult.height) > 1)
    {
        // Height difference between left and right too great
        return{false, 0};
    }
    return{true, std::max(leftResult.height, rightResult.height)+1};

    /*
    bool isBalanced = abs(leftResult.height - rightResult.height) <= 1;
    int height = std::max(leftResult.height, rightResult.height);
    return {isBalanced, height};
    */
}
/*
 * Conclusion:
 * I tried working it out on paper and had the right idea. I came up with the idea
 * to use a struct to track both the height and balanced status and saw the book
 * used it too. I get the concept since we had this problem on the 343 midterm.
 *
 * Results:
 * All tests PASSED
 * Average running time:    2 us
 * Median running time:    <1 us
 */

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>> &tree) {
    return BalancedHelper(tree).balanced;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree"};
    return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                           &IsBalanced, DefaultComparator{}, param_names);
}
