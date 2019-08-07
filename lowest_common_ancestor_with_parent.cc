#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

/*
 * Exercise 9.4 - Compute the Lowest Common Ancestor when Nodes have Parent Pointers
 * The lowest common ancestor the the node at the lowest level that has two
 * nodes as children. Find the LCA when each binary tree node has a pointer to the
 * parent node.
 *
 * Initial Thoughts:
 * I worked it out on paper for a bit. My plan is to first get the height of
 * both nodes by following the parents to the root. From there,
 * I can increment the further one to the same level, then follow the parents
 * and check if they're equal. If they are, then we've found the LCA.
 */

/*
 * Helper function to return the number of edges to the root.
 */
int GetHeight(const BinaryTreeNode<int> *node)
{
    int height = 0;
    auto pNode = node;
    // Iterate up to the root
    while(pNode->parent)
    {
        height++;
        pNode = pNode->parent;
    }
    return height;
}

// Need a recursive function to follow the parent pointers to the root.
BinaryTreeNode<int> *LCA(const unique_ptr<BinaryTreeNode<int>> &node0,
                         const unique_ptr<BinaryTreeNode<int>> &node1) {
    BinaryTreeNode<int> *p0 = node0.get();
    BinaryTreeNode<int> *p1 = node1.get();

    // Get height of both nodes
    int height0 = GetHeight(p0);
    int height1 = GetHeight(p1);

    /* Implied equal height after passing conditionals
    // For whichever node is lower, bring it up to the same level
    if(height0 == height1) // Equal height
    {
        // Follow nodes' respective parents until LCA found
    }
    if(height0 < height1)
    {
        // Node1 is lower. Bring it up to the same level as Node0
        for(int i=0; i < height1 - height0; i++)
        {
            p1 = p1->parent;
        }

    }
    else if(height1 < height0)
    {
        // Node0 is lower. Bring it up to the same level as Node1
        for(int i=0; i < height0 - height1; i++)
        {
            p0 = p0->parent;
        }
    }
    // Pointers now at same height. Go up until parent found
    while(p0->parent != p1->parent)
    {
        p0 = p0->parent;
        p1 = p1->parent;
        // Will exit this loop once equal
    }
    return p0->parent;
     */

    // There were a few things wrong in my code. I have the concept down and decided to
    // follow the book's implementation below. It's more clever and neat.

    if(height1 > height0) std::swap(p0, p1);
    int heightDifference = abs(height0 - height1);

    while(heightDifference--)
    {
        p0 = p0->parent;
    }

    // Ascend both nodes in tandem until LCA found
    while(p0 != p1)
    {
        p0 = p0->parent, p1 = p1->parent;
    }
    return p0;
}

/*
 * Conclusion:
 * I'm proud about getting the concept down after working out a few examples on paper. It turned
 * out to be the correct solution. I referred to the book whenever I had trouble with how things
 * worked, such as declaring the BinaryTreeNode pointer objects. Feeling confident about this
 * question if it were to appear again.
 *
 * Results:
 * All tests PASSED!
 * Average running time:   <1 us
 * Median running time:    <1 us
 */

int LcaWrapper(TimedExecutor &executor,
               const unique_ptr<BinaryTreeNode<int>> &tree, int key0,
               int key1) {
    const unique_ptr<BinaryTreeNode<int>> &node0 = MustFindNode(tree, key0);
    const unique_ptr<BinaryTreeNode<int>> &node1 = MustFindNode(tree, key1);

    auto result = executor.Run([&] { return LCA(node0, node1); });

    if (!result) {
        throw TestFailure("Result can not be nullptr");
    }
    return result->data;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
    return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                           "lowest_common_ancestor.tsv", &LcaWrapper,
                           DefaultComparator{}, param_names);
}
