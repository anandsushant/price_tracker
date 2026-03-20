#ifndef TRACKER_HPP 
#define TRACKER_HPP 

#include <main.hpp>

#include <deque>
#include <cassert>
#include <algorithm>

struct Tick_U {
    int timestamp;
    int price;
    long long prefix_sum;
};

/**
 * @class: PriceTracker
 * @brief: A class to manage the state of buffer_ of Tick values
 *         where we update the buffer_ by a stream of tick values
 *         inserting them using update() and then calculating 
 *         certain metrics and answering queries.
 */

class PriceTracker {
    
    public:

    PriceTracker(int window) : W(window) {}
    void update(const Tick& t);
    double getAverage();
    double getAverage(const int& k); // k = last_k_seconds

    int getMax();
    int getMax(const int& k); // k = last_k_seconds

    private:
    
    std::deque<Tick_U> buffer_;
    std::deque<Tick> maxDeque_;
    long long sum_{};
    int W;
};

#endif  //TRACKER_HPP