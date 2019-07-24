#include "list_node.h"
#include "test_framework/generic_test.h"

/*
 * Exercise 7.2 - Reverse a Single Sublist
 * Reverse a single sublist within a larger linked list. Take two
 * integers for the start and end of a sublist, starting at 1.
 *
 * Initial Thoughts:
 * I played with the problem on paper and found one approach that might work.
 * This problem is a lot more difficult since we're using a singly linked list.
 * First traverse to node Start - 1. Make a new pointer and traverse to Finish
 *      That node's next will point to the node at Finish.
 *      Now increment Start pointer and make a new pointer go to --Finish.
 *      Start now equals the node at Finish.
 *
 * Essentially it loops from Start to Finish to continuously select the next node
 */
shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {

    // I used the book's solution first to get more comfortable with writing code
    // using their provided linked list class

    auto dummyHead = make_shared<ListNode<int>>(ListNode<int>{0, L});
    auto sublistHead = dummyHead;
    int k = 1;

    // Get a pointer to point to the start of the sublist
    while(k++ < start)
    {
        sublistHead = sublistHead->next;
    }

    // Reverses sublist
    auto sublistIterator = sublistHead->next;
    while(start++ < finish)
    {
        auto temp = sublistIterator->next;
        sublistIterator->next = temp->next;
        temp->next = sublistHead->next;
        sublistHead->next = temp;
    }
    return dummyHead->next;

    // Results: ALL PASSED
    // Average running time:   23 us
    // Median running time:    <1 us
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L", "start", "finish"};
    return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                           &ReverseSublist, DefaultComparator{}, param_names);
}
