#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

#include <vector>

/*
 * Exercise 8.7 - Circular Queue
 * Create a queue API implemented with an Array.
 * Must include a constructor, enqueue, dequeue, and size functions.
 * Queue must dynamically resize to support an arbitrarily
 * large number of elements.
 *
 * Initial Thoughts:
 * I think I learned about this in 342. Start and end indices keep track of where
 * the queue begins and ends, and constantly shifts down the array.
 * The array also resizes once a push operation reaches the end. Maybe
 * it can double in size.
 */
class Queue {
public:
    /*
     * Constructor for the initial size of elements
     */
    Queue(size_t capacity)
    {
        //head = 0; // head index
        //tail = 0; // tail index
    }
    explicit Queue(int capacity) : arr(capacity) {}

    void Enqueue(int x) {
        /*
        if(tail+1 == arr.size()) // Would I need this? Vectors already allow arbitrary sizes
        {

        }
         */
        //arr.push_back(x);
        //++tail;
        if(numElements == arr.size()) // needs to be resized
        {
            std::rotate(arr.begin(), arr.begin()+head, arr.end());
            head = 0, tail = numElements;
            arr.resize(arr.size() * kScaleFactor); // I thought vectors dynamically resized or
            // supported infinite push_back operations
        }
        arr[tail] = x;
        tail = (tail + 1) % arr.size(), ++numElements;
        // tail is equal to itself + 1, then mod with the new size(). bit confused...
    }

    int Dequeue() {
        --numElements;
        int retVal = arr[head];
        /*
        auto i = arr.begin() + head++;
        arr.erase(i); // Remove the element at the head and increment it up
         */
        head = (head + 1) % arr.size(); // also confused by the mod
        return retVal;
    }

    int Size() const {
        // return tail - head;
        return numElements;
    }

private:
    // Underlying array
    const int kScaleFactor = 2;
    int head = 0, tail = 0, numElements = 0;
    std::vector<int> arr; // holds elements
};

/*
 * Conclusion:
 * My implementation was on the right track, but I got confused by
 * not knowing how a vector's ability to dynamically resize would
 * work within this queue API. I referred to the solution and fixed
 * my own to match it.
 *
 * Results:
 * All tests Passed!
 * Average running time:   15 us
 * Median running time:    <1 us
 */

struct QueueOp {
    enum {
        kConstruct, kDequeue, kEnqueue, kSize
    } op;
    int argument;

    QueueOp(const std::string &op_string, int arg) : argument(arg) {
        if (op_string == "Queue") {
            op = kConstruct;
        } else if (op_string == "dequeue") {
            op = kDequeue;
        } else if (op_string == "enqueue") {
            op = kEnqueue;
        } else if (op_string == "size") {
            op = kSize;
        } else {
            throw std::runtime_error("Unsupported queue operation: " + op_string);
        }
    }

    void execute(Queue &q) const {
        switch (op) {
            case kConstruct:
                // Hack to bypass deleted assign operator
                q.~Queue();
                new(&q) Queue(argument);
                break;
            case kDequeue: {
                int result = q.Dequeue();
                if (result != argument) {
                    throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                                      ", got " + std::to_string(result));
                }
            }
                break;
            case kEnqueue:
                q.Enqueue(argument);
                break;
            case kSize: {
                int s = q.Size();
                if (s != argument) {
                    throw TestFailure("Size: expected " + std::to_string(argument) +
                                      ", got " + std::to_string(s));
                }
            }
                break;
        }
    }
};

template<>
struct SerializationTraits<QueueOp> : UserSerTraits<QueueOp, std::string, int> {
};

void QueueTester(const std::vector<QueueOp> &ops) {
    Queue q(0);
    for (auto &op : ops) {
        op.execute(q);
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"ops"};
    return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                           &QueueTester, DefaultComparator{}, param_names);
}
