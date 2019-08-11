#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_utils.h"

using std::vector;
using std::priority_queue;

/*
 * Exercise 10.4 - Compute the k Closest Stars
 * Consider a coordinate system where Earth is at (0,0,0) and stars
 * have coordinates relative to it.How would you compute the k stars
 * which are closest to Earth?
 *
 * Initial Thoughts:
 * I can use a min heap and add stars to it based on their distance
 * from earth. Would need a distance function to calculate the straight line path.
 *
 * The problem also states the approximate number of stars in the Milky Way,
 * I could use a vector with that size. I remember from 343 there were two ways to
 * insert an element into the heap. One placing it at the end then percolating up,
 * and the other requiring all elements to be present from the start.
 *
 * Since we're given the entire vector of stars, it would be best to build
 * the heap using the second method. The return array will have k elements.
 * If a new lowest element arrives, one at the end of the heap will need
 * to be discarded. Maybe I can maintain two heaps, a min and MAX heap.
 * The max heap would store pointers to the greatest element in the min heap,
 * so we could easily discard them.
 */

struct Star {
    // They've also overloaded the comparison operator
    bool operator<(const Star &that) const {
        return Distance() < that.Distance();
    }
    // Luckily distance is already calculated here
    double Distance() const { return sqrt(x * x + y * y + z * z); }
    // double distance = Distance();
    double x, y, z;
};


vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin,
                               const vector<Star>::const_iterator &stars_end,
                               int k) {
    // Declare two heaps with k elements. Whenever it's at full capacity (k), every
    // enqueue would need a dequeue, since we only care about the top k elements.
    // ... Actually, it wouldn't work because heaps don't allow deletion besides
    //     at the top node. I'll just make one big heap and pop the top k elements
    //     into the return array.
    priority_queue<Star> maxHeap;
    //priority_queue<Star> *maxHeap;
    // Enqueue the first k stars
    //auto pos = stars_begin;
    /*
    for(int i=0; i<k; i++)
    {
        minHeap.emplace(pos->Distance());
        pos++;
    }
    */
    /*
    for(auto pos = stars_begin; pos != stars_end; pos++)
    {
        maxHeap.emplace(*pos); // dereference the star?
    }
     */
    while(stars_begin != stars_end)
    {
        maxHeap.emplace(*stars_begin++);
        if(maxHeap.size() == k + 1)
        {
            maxHeap.pop();
        }
    }

    vector<Star> retVal;
    while(!maxHeap.empty())
    {
        retVal.push_back(maxHeap.top());
        maxHeap.pop();
        // It will add to the vector with the furthest of the k closest first.
        // Need to return it in reverse order.
    }
    return {std::rbegin(retVal), std::rend(retVal)};
}

/*
 * Conclusion:
 * To solve this problem I had to maintain a max heap containing only k stars.
 * The top of the heap would be the furthest star. Once the initial k stars
 * have been added, continuously pop off the top star, which would be the furthest
 * from earth.
 *
 * Results:
 * All tests passed!
 * Average running time:  235 us
 * Median running time:    <1 us
 */

template<>
struct SerializationTraits<Star> : UserSerTraits<Star, double, double, double> {
};

std::ostream &operator<<(std::ostream &out, const Star &s) {
    return out << s.Distance();
}

bool Comp(const vector<double> &expected, vector<Star> output) {
    if (output.size() != expected.size()) {
        return false;
    }

    std::sort(begin(output), end(output));

    for (int i = 0; i < output.size(); ++i) {
        if (!DefaultComparator()(output[i].Distance(), expected[i])) {
            return false;
        }
    }
    return true;
}

vector<Star> FindClosestKStarsWrapper(const vector<Star> &stars, int k) {
    return FindClosestKStars(cbegin(stars), cend(stars), k);
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"stars", "k"};
    return GenericTestMain(args, "k_closest_stars.cc", "k_closest_stars.tsv",
                           &FindClosestKStarsWrapper, &Comp, param_names);
}
