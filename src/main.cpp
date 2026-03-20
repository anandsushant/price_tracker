/**
 * @author: Sushant Anand | sushantxanand@gmail.com
 * @date  : 14-03-2026 1:00 am
 */

#include <iostream>
#include <track.hpp>
#include <client.hpp>

int main () {

    std::cout << "Starting Communication...\n";
    Comm comm;
    std::cout << "Starting tracker...\n";
    PriceTracker pt(1000);

    comm.start();
    Tick tick;
    std::cout << "Running tracker....\n";
    while(true) {
        comm.reader(tick);
        pt.update(tick);
    }
    return 0;
}