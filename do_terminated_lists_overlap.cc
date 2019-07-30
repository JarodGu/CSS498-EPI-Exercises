#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::shared_ptr;

/*
 * Exercise 7.4 - Test for Overlapping Lists
 * Create a function that takes two non-cyclic singly linked lists
 * and determines if they both share a common node. Both lists would
 * converge at the common node and continue on the same path.
 *
 * Initial Thoughts:
 * I can traverse down both linked lists via two pointers and for
 * each node, check if their next node is equal to each other.
 */

// Helper function to return the size of a linked list
int Length(shared_ptr<ListNode<int>> L)
{
    int length = 0;
    while(L)
    {
        ++length, L=L->next;
    }
    return length;
}

// Iterates a pointer through the list by a certain number of nodes K
void AdvanceListByK(int k, shared_ptr<ListNode<int>> *L)
{
    while(k--)
    {
        *L = (*L)->next;
    }
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
        shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
    shared_ptr<ListNode<int>> listA = l0, listB = l1;
    /*
    while(listA && listB) // while both pointers are not null
    {
        if(*listA == *listB) // if the pointers are equal
        {
            return listA;
        }
        // Increment pointers
        listA = listA->next;
        listB = listB->next;
    }
    return nullptr; // common node never encountered. Return nullptr
     */
    // Results: 6 of 106 tests passed
    // My solution overlooks the fact that an overlapping node can occur
    // anywhere in the list, thus I cannot increment both in parallel and
    // thus for every node in ListA, must search all nodes in ListB.
    // Complexity of this solution is O(n^2)

    int listALength = Length(l0), listBLength = Length(l1);

    // Advance the longer list to get equal length lists
    AdvanceListByK(abs(listALength - listBLength), listALength > listBLength ? &l0 : &l1);

    while(l0 && l1 && l0 != l1)
    {
        l0 = l0->next, l1 = l1->next; // We can use the parameters to traverse since they aren't const
    }
    return l0; // returns nullptr which implies no overlapping nodes

    //Results:
    // All 106 tests PASSED
    // Average running time: 197us
    // Median running time: <1us
}

void OverlappingNoCycleListsWrapper(TimedExecutor &executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
    if (common) {
        if (l0) {
            auto i = l0;
            while (i->next) {
                i = i->next;
            }
            i->next = common;
        } else {
            l0 = common;
        }

        if (l1) {
            auto i = l1;
            while (i->next) {
                i = i->next;
            }
            i->next = common;
        } else {
            l1 = common;
        }
    }

    auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

    if (result != common) {
        throw TestFailure("Invalid result");
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
    return GenericTestMain(
            args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
            &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
