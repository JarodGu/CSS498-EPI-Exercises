#include <memory>
#include "list_node.h"
#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::shared_ptr;

/*
 * Exercise 7.3 - Test for Cyclicity
 *
 * Linked lists usually end with null, but it's possible to create a cycle
 * by making the "next" field of an element reference an earlier one.
 *
 * Write a program that takes a list head and returns null if
 * there does not exist a cycle, or the node of the start of a cycle
 * if it exists. Length of the list is not given.
 *
 * Initial Thoughts:
 * Pointers are stored by an address, so a brute force method would
 * be to have an array of addresses in the list and compare each traversed node
 * with one in that address "book."
 *
 * Maybe that "address book" could be a list or array. List might work better
 */

// Helper function to check if a vector contains a specific node
bool ContainsNode(const std::vector<ListNode<int>> &addressBook, const ListNode<int> &key)
{
    for(int i=0; i<addressBook.size(); i++)
    {
        if(addressBook[i] == key){
            return true;
        }
    }
    return false;
}

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>> &head) {
    // TODO - you fill in here.
    // While traversing the list, compare the node's->next to entries in a vector
    // and if one doesn't exist, add it.
    // Return null if we reach null
    // Return the cyclic node if a node->next matches one in the vector

    // Our vector stores nodes by their address
    /*
    std::vector<ListNode<int>> addressBook;

    auto dummyHead = make_shared<ListNode<int>>(ListNode<int>{0, head});
    auto pHead = dummyHead;

    while (pHead != nullptr) {
        if (ContainsNode(addressBook, *pHead)) { // found
            return pHead;
        } else { // not found
            addressBook.push_back(*pHead);
        }
        pHead = pHead->next;
    }
    // No cycles found and nullptr reached. Return nullptr
    return nullptr;
     */
    // Results:
    // First two tests passed, but errors occured on the others
    // --------------------------------------------------------------------
    // Now referring to the book's solution. It's much more clever.
    // Two iterators are used, one slow and one fast. If the fast iterator
    // catches up to the slow one, then there was a cycle.

    shared_ptr<ListNode<int>> fast = head, slow = head;

    while(fast && fast->next) {
        slow = slow->next, fast = fast->next->next; // fast is twice as fast
        if (slow == fast) {
            // there's a cycle so we need to calculate the cycle's length
            int cycleLength = 0;
            do {
                ++cycleLength;
                fast = fast->next;
            } while (slow != fast);

            // Finds the start of the cycle
            auto cycleLengthAdvancedIter = head;
            while (cycleLength--)
            {
                cycleLengthAdvancedIter = cycleLengthAdvancedIter->next;
            }
            auto iter = head;
            // Both iterators advance in tandem
            while(iter != cycleLengthAdvancedIter)
            {
                iter = iter->next;
                cycleLengthAdvancedIter = cycleLengthAdvancedIter->next;
            }
            return iter; // iter is start of cycle
        }
    }
    return nullptr; // no cycle
    // Results: All tests PASSED
    // Average running time:   88 us
    // Median running time:    <1 us
}

void HasCycleWrapper(TimedExecutor &executor,
                     const shared_ptr<ListNode<int>> &head, int cycle_idx) {
    int cycle_length = 0;
    if (cycle_idx != -1) {
        if (!head) {
            throw std::runtime_error("Can't cycle empty list");
        }
        shared_ptr<ListNode<int>> cycle_start, cursor = head;
        while (cursor->next) {
            if (cursor->data == cycle_idx) {
                cycle_start = cursor;
            }
            cursor = cursor->next;
            cycle_length += !!cycle_start;
        }
        if (cursor->data == cycle_idx) {
            cycle_start = cursor;
        }
        if (!cycle_start) {
            throw std::runtime_error("Can't find a cycle start");
        }
        cursor->next = cycle_start;
        cycle_length++;
    }
    shared_ptr<ListNode<int>> result =
            executor.Run([&] { return HasCycle(head); });

    if (cycle_idx == -1) {
        if (result != nullptr) {
            throw TestFailure("Found a non-existing cycle");
        }
    } else {
        if (result == nullptr) {
            throw TestFailure("Existing cycle was not found");
        }

        auto cursor = result;
        do {
            cursor = cursor->next;
            cycle_length--;
            if (!cursor || cycle_length < 0) {
                throw TestFailure(
                        "Returned node does not belong to the cycle or is not the "
                        "closest node to the head");
            }
        } while (cursor != result);

        if (cycle_length != 0) {
            throw TestFailure(
                    "Returned node does not belong to the cycle or is not the closest "
                    "node to the head");
        }
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "head", "cycle_idx"};
    return GenericTestMain(args, "is_list_cyclic.cc", "is_list_cyclic.tsv",
                           &HasCycleWrapper, DefaultComparator{}, param_names);
}
