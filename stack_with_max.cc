#include <stdexcept>
#include <stack>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

#include "list_node.h"

using namespace std;
using std::length_error;

/*
 * Exercise 8.1 - Stack with Max API
 * Design a stack from scratch that includes a function
 * that returns the max element.
 *
 * Initial Thoughts:
 * I've already done this in 342 so this is just review. Linked list seems
 * to be the easiest implementation so I might use the provided linked list class
 * files for it. I can also use the c++ library stack class
 *
 */

class Stack {
public:
    /*
     * Returns whether the stack is empty
     */
    bool Empty() const {
        // return s.empty();
        return element_with_cached_max_.empty();
    }

    /*
     * Returns the greatest element in the stack.
     * Returns -INT_MAX if stack is empty
     */
    int Max() const {
        /*
        stack<int> temp;
        int max = -INT_MAX;

        // Pop elements onto temp stack
        while(!s.empty())
        {
            if(s.top() > max) max = s.top();
            temp.push(s.top());
            s.pop();
        }

        // Restore elements from original stack
        while(!temp.empty())
        {
            s.push(temp.top());
            temp.pop();
        }
        return max;
         */
        return element_with_cached_max_.top().max;
    }

    /*
     * Pops off the top element in the stack and returns its value
     */
    int Pop() {
        /*
        int retVal = s.top();
        s.pop();
        return retVal;
         */
        int pop_element = element_with_cached_max_.top().element;
        element_with_cached_max_.pop();
        return pop_element;
    }

    /*
     * Pushes an integer value to the top of the stack
     */
    void Push(int x) {
        /*
        s.push(x);
         */
        // The line below pushes the element onto the stack AND also
        // stores info about what was the max element in the stack.
        // ElementWithCachedMax.element is what we push
        // ElementWithCachedMax.max is the max element cached
        element_with_cached_max_.push(
                ElementWithCachedMax{x, max(x, Empty() ? x : Max())} );
    }

private:
    //stack<int> s;
    struct ElementWithCachedMax {
        int element, max;
    };
    stack<ElementWithCachedMax> element_with_cached_max_;
};

// Decided to implement by wrapping the C++ stack class
// into the required interface.
// All tests passed!
// Average running time:    7 ms
// Median running time:    <1 us

// Now for the book's solution. It's complex and I never would have guessed it.
// They cache the max element while pushing values onto the stack.
// I've commented out my solution above.

// Book's solution: It takes longer at the cost of O(1) memory allocation
// Average running time:   29 us
// Median running time:    <1 us

struct StackOp {
    std::string op;
    int argument;
};

template<>
struct SerializationTraits<StackOp> : UserSerTraits<StackOp, std::string, int> {
};

void StackTester(const std::vector<StackOp> &ops) {
    try {
        Stack s;
        for (auto &x : ops) {
            if (x.op == "Stack") {
                continue;
            } else if (x.op == "push") {
                s.Push(x.argument);
            } else if (x.op == "pop") {
                int result = s.Pop();
                if (result != x.argument) {
                    throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                                      ", got " + std::to_string(result));
                }
            } else if (x.op == "max") {
                int result = s.Max();
                if (result != x.argument) {
                    throw TestFailure("Max: expected " + std::to_string(x.argument) +
                                      ", got " + std::to_string(result));
                }
            } else if (x.op == "empty") {
                int result = s.Empty();
                if (result != x.argument) {
                    throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                                      ", got " + std::to_string(result));
                }
            } else {
                throw std::runtime_error("Unsupported stack operation: " + x.op);
            }
        }
    } catch (length_error &) {
        throw TestFailure("Unexpected length_error exception");
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"ops"};
    return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                           &StackTester, DefaultComparator{}, param_names);
}
