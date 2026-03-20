
#include <track.hpp>
#include <iostream>

void PriceTracker::update(const Tick& t) {

    long long ps = buffer_.empty() ? t.price : buffer_.back().prefix_sum + ps;

    buffer_.push_back({t.timestamp, t.price, ps});
    // std::cout << "t taken: " << t.timestamp << " | price: " << t.price << "\n";
    sum_ += t.price;

    while(!maxDeque_.empty() && maxDeque_.back().price < t.price) {
        maxDeque_.pop_back();
    }

    maxDeque_.push_back({t.timestamp, t.price});

    while (!buffer_.empty() && buffer_.front().timestamp < t.timestamp - W) {
        auto old = buffer_.front();
        buffer_.pop_front();
        sum_ -= old.price;
        if (maxDeque_.front().price == old.price) {
            maxDeque_.pop_front();
        }
    }
    return;
}

double PriceTracker::getAverage() {
    return (double) (sum_/buffer_.size());
}

double PriceTracker::getAverage(const int& k) {

    assert(k <= W);
    int new_k = std::min(k, (int)buffer_.size());
    
    int start_time = buffer_.back().timestamp - new_k;

    auto it = std::lower_bound(buffer_.begin(), buffer_.end(), start_time, [](const Tick_U& t, int value){
                return t.timestamp < value;
              });
        
    int idx = it - buffer_.begin();
    int count = buffer_.size() - idx;

    long long total = (idx == 0) ? buffer_.back().prefix_sum : buffer_.back().prefix_sum - buffer_[idx-1].prefix_sum;

    return (double) total/count;
} 

int PriceTracker::getMax() {
    return maxDeque_.front().price;
}

int PriceTracker::getMax(const int& k) {
    
    assert(k <= W);
    int new_k = std::min(k, (int)buffer_.size());
    
    int start_time = buffer_.back().timestamp - new_k;

    auto it = maxDeque_.begin();
    while(1) {
        if(it->timestamp < start_time) {
            it++;
        } else {
            return it->price;
        }
    }
    return 0;

}