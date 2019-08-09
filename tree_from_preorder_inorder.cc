#include <vector>
#include <memory>
#include <unordered_map>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"

using std::vector;

/*
 * Exercise 9.11 - Reconstruct a Binary Tree from Traversal Data
 * There are many possible tree structures that satisfy a given
 * traversal sequence (inorder, pre-order, and post-order). However, when
 * given at least 2 different traversals, there exists 1 unique tree
 * that satisfied both. Reconstruct this tree given 1 in-order traversal
 * and 1 pre-order traversal.
 *
 * Initial Thoughts
 * Really had to work this one out on a board to figure out a pattern.
 * The two example traversals are:
 * Preorder:    <F, B, A, E, H, C, D, I, G>
 * Inorder:     <H, B, F, E, A, C, D, G, I>
 *
 * We'll build the tree using the in-order sequence, and for each node,
 * look at the pre-order sequence to know precisely where to put it.
 *
 * 1. H is the root
 * 2. B is next. It can go left or right of H. Refer to pre-order sequence
 *    and B is before H, therefore B is left.
 * The algorithm is something like that. Comparing the inorder[i] with preorder[j]
 *
 * What helper functions would I need (if any)?
 * Maybe some acrobatic pointer that traverses up and down? Recursion can do this
 * I'd need to pass the preorder and inorder vectors.
 *
 * Traverse the new tree in pre-order. Build the current node, then think:
 * Could B go here? If so, build it.
 * Go left of B, could F go here? No? Could it go right of B? No? Go back up.
 *
 * A for loop would require escaping the recursive function back up to the top.
 * I'll pass a pre-order index variable through the functions whenever a node it built.
 *
 * Now for the comparison that tells if it's a valid placement.
 * Is it to the left or right of the last placed node?
 *  If left, the place left, or right.
 */
unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorderHelper(
        const vector<int> &preorder, size_t preorderStart, size_t preorderEnd,
        size_t inorderStart, size_t inorderEnd,
        const std::unordered_map<int, size_t>& nodeToInorderIndex)
{
    if(preorderEnd <= preorderStart || inorderEnd <= inorderStart)
    {
        return nullptr;
    }
    size_t rootInorderIndex = nodeToInorderIndex.at(preorder[preorderStart]);
    size_t leftSubtreeSize = rootInorderIndex - inorderStart;

    // This is one BIG return statement that builds a binary tree node with
    // completed left and right subtrees
    return std::make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
        preorder[preorderStart],
        // Recursively build left subtree
        BinaryTreeFromPreorderInorderHelper(
                preorder, preorderStart + 1,
                preorderStart + 1 + leftSubtreeSize, inorderStart,
                rootInorderIndex, nodeToInorderIndex),
        // Recursively bild left subtree
        BinaryTreeFromPreorderInorderHelper(
                preorder, preorderStart + 1 + leftSubtreeSize, preorderEnd,
                rootInorderIndex + 1, inorderEnd, nodeToInorderIndex)
    });
}

/*
 * Conclusion:
 * Working the problem out on the board helped a ton, but the problem
 * was just way too difficult. I typed out
 * the book's solution and don't understand most of it. They used a hash table
 * for something. Probably the most difficult problem yet.
 *
 * Results:
 * All tests passed
 * Average running time:   40 us
 * Median running time:    <1 us
 */
unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
        const vector<int> &preorder, const vector<int> &inorder) {

    // Book's solution uses a hash table
    std::unordered_map<int, size_t> nodeToInorderIndex;
    for(size_t i=0; i<inorder.size(); ++i)
    {
        nodeToInorderIndex.emplace(inorder[i], i);
    }
    return BinaryTreeFromPreorderInorderHelper(
            preorder, 0, preorder.size(), 0, inorder.size(), nodeToInorderIndex);
}


int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"preorder", "inorder"};
    return GenericTestMain(
            args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
            &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
