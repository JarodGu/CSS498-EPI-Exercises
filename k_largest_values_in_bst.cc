#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/generic_test.h"

using std::unique_ptr;
using std::vector;

/*
 * Exercise 14.3 - Find the K Largest values in a BST
 * Write a function that returns an array with the k
 * largest values in a BST.
 *
 * Initial Thoughts:
 * This seems very easy.Inorder traversal is Left->Node->Right,
 * so the opposite of Right->Node->Left should return elements from
 * greatest to least. Whenever I get to the node step, I'll want
 * to push the value onto a return vector. If its size == k, then
 * return the vector.
 *
 * Wondering if it would be possible to do it iteratively.
 */
void FindKLargestInBSTHelper(const unique_ptr<BstNode<int>> &root, int k, vector<int> *retVal)
{
    /*
    if(root != nullptr)
    {
        FindKLargestInBSTHelper(root->right, k, retVal);
        if(retVal.size() < k)
        {
            retVal.push_back(root->data);
        }
        FindKLargestInBSTHelper(root->left, k, retVal);
    }
     */
    if(root && retVal->size() < k)
    {
        FindKLargestInBSTHelper(root->right, k, retVal);
        if(retVal->size() < k)
        {
            retVal->push_back(root->data);
            FindKLargestInBSTHelper(root->left, k, retVal);
        }
    }
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>> &tree, int k)
{
    vector<int> retVal;
    FindKLargestInBSTHelper(tree, k, &retVal);
    return retVal;
}

/*
 * Conclusion:
 * My solution worked for this problem. I compared it to the book's solution
 * and their's had the same idea but was structured differently. Their's was
 * more efficient with a time complexity of O(h+k) where h is the tree height
 * and k the number of elements to return. This is probably due to them checking if
 * the k elements have been found before traversing right AND before
 * adding a new element to the return vector.
 *
 * My Results:
 * All test passed!
 * Average running time:   40 us
 * Median running time:    10 us
 *
 * Solution Results:
 * Average running time:   25 us
 * Median running time:     7 us
 */
int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree", "k"};
    return GenericTestMain(args, "k_largest_values_in_bst.cc",
                           "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                           &UnorderedComparator<std::vector<int>>, param_names);
}
