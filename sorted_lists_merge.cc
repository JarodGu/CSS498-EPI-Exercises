#include "list_node.h"
#include "test_framework/generic_test.h"

/*
 * Exercise 7.1 - Merge Two Sorted Lists
 * Create a function that merges two sorted single-linked lists and
 * returns their merge.
 * NOTE: I can only change a node's "next" field
 *
 * Initial Thoughts:
 * Since I'm returning a new linked list, I'll need a function to create a node
 * and set the next to point to the next one in order.
 * I can also maintain two indices to track my current position each of the
 * two linked lists.
 */

/*
 * Solution function used to append a node to an existing linked list
 */
void AppendNode(shared_ptr<ListNode<int>> *node, shared_ptr<ListNode<int>> *tail) {
    (*tail)->next = *node;
    *tail = *node; // update tail
    *node = (*node)->next;
}

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
    /*
     * My Code Below:
     * ---------------
    // Pointers to the start of each list are L1 and L2.
    // They are shared pointers to allow other pointers to point at them
    ListNode<int> retVal;

    ListNode<int> L1index, L2index;
    L1index.next = L1;
    L2index.next = L2;

    // I can have two while loops. If L1 reaches the end, then just keep adding
    // elements from L2.
    // If L2 reaches the end, then add the remaining elements from L1

    while(L1index.next != nullptr)
    {
        // If L1 node is less than L2 node
        if(L1index.data <= L2index.data)
        {
            retVal.data = L1index.data;
        }
        else // L2 > L1
        {
            retVal.data = L2index.data;
        }
    }
    while(L2index.next != nullptr)
    */

    // --------------------------------------------
    // I referred to the solution for this one to get an idea of how to use
    // the provided list_node.h class


    // We are only allocating O(1) memory because we're using shared_ptr's
    // which allow the merged list to point to the existing lists memory while still
    // being its own list.
    shared_ptr<ListNode<int> > dummyHead(new ListNode<int>);
    auto currentIndex = dummyHead; // auto allows it to infer its type. Bit confused as to why

    while (L1 && L2) {
        // Is L1's data less than L2's data?
        // If so, append L1 to the merged list
        // Otherwise, append L2 to the merged list
        // Pass the tail or index parameter to increment it
        AppendNode(L1->data <= L2->data ? &L1 : &L2, &currentIndex);
    }

    // Either L1 or L2 ended up finishing early, so we can just
    // append the remainder of the other list.

    currentIndex->next = L1 ? L1 : L2; // Does L1 exist? (ie. not nullptr) If so, append it, otherwise append L2.

    return dummyHead->next;

    /*
     * SOLUTION RESULTS:
     * All tests passed!
     * Average running time:   26 us
     * Median running time:    <1 us
     */
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L1", "L2"};
    return GenericTestMain(args, "sorted_lists_merge.cc",
                           "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                           DefaultComparator{}, param_names);
}
