#include <memory>
#include "bst_node.h"
#include "test_framework/generic_test.h"

using std::unique_ptr;

/*
 * Exercise 14.2 - Find the First Key Greater than a Given Value in a BST
 * Write a program that takes as input a BST and key K and returns the
 * first key that would appear in an inorder traversal which is greater than
 * the input value.
 *
 * Initial Thoughts:
 * The brute force solution would be to start traversing the tree inorder until
 * I reach the key k, then return the node after it. This doesn't however take
 * advantage of the BST structure. I might be able to traverse down
 * then perform an action once I'm near the key.
 *
 * Maybe I can also pass a pointer to the closest element greater than k. What
 * would the base case be? Maybe reaching nullptr
 */
/*
 * Helper function. The candidate points to a node along the path to the key
 * and is changed when a node less than the current candidate AND greater than k
 * is encountered. Once at nullptr, return this candidate.
 */
/*
BstNode<int> *FindFirstGreaterThanKHelper(const unique_ptr<BstNode<int>> &root,
                                          BstNode<int> *candidate, int k)
{
    // Base case
    if (root == nullptr)
    {
        return candidate;
    }
    // Update candidate
    if (root->data < candidate->data && root->data > k)
    {
        candidate = root.get();
    }
    // BST Traversal to k
    k <= root->data ? FindFirstGreaterThanKHelper(root->left, candidate, k)
                    : FindFirstGreaterThanKHelper(root->right, candidate, k);
    return nullptr; // not used
}
 */

/*
 * Book's solution is like an iterative version of my implementation.
 * Traverse a tree until we reach a nullptr. Store the closest node
 * greater than k in candidate. When we traverse left, it means
 * the node is less than our current candidate, so update it. When
 * we traverse right, it will be greater than the current candidate
 * so no need to update.
 */
BstNode<int> *FindFirstGreaterThanK(const unique_ptr<BstNode<int>> &tree,
                                    int k)
{
    BstNode<int> *subtree = tree.get(), *candidate = nullptr;
    while(subtree)
    {
        if(subtree->data > k)
        {
            candidate = subtree;
            subtree = subtree->left.get();
        }
        else // Root and all keys in left subtree are <= k, so skip them
        {
            subtree = subtree->right.get();
        }
    }
    return candidate;
    // return FindFirstGreaterThanKHelper(tree, tree.get(), k);
}

/*
 * Conclusion:
 * My recursive implementation was on the right track,
 * but it's much more efficient to traverse a BST iteratively.
 * Time Complexity of this one is O(h) where h is the height of
 * the tree, and space complexity is O(1).
 *
 * Results:
 * All tests passed
 * Average running time:    2 us
 * Median running time:     2 us
 */
int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>> &tree, int k)
{
    auto result = FindFirstGreaterThanK(tree, k);
    return result ? result->data : -1;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree", "k"};
    return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                           "search_first_greater_value_in_bst.tsv",
                           &FindFirstGreaterThanKWrapper, DefaultComparator{},
                           param_names);
}
