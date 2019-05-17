#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>

using namespace std::chrono;
using hrc = high_resolution_clock;

int main(int argc, char** argv)
{
    // Time a one second sleep using the high resolution clock

    hrc::time_point t1 = hrc::now();
    std::this_thread::sleep_for(duration<double>(1));
    hrc::time_point t2 = hrc::now();

    nanoseconds deltaT = t2 - t1;

    std::cout <<
        "Time for a 1 second sleep in nanoseconds: " <<
         deltaT.count() << std::endl;

    // Convert current time to a timestamp in nanoseconds

    uint64_t timestamp = 
         duration_cast<nanoseconds>(
             hrc::now().time_since_epoch()).count();

    std::cout <<
        "Time since epoch in nanoseconds: " << timestamp << std::endl;

    // Convert the nanosecond count back to a duration

    nanoseconds sinceEpoch(timestamp);

    std::cout <<
        "Round-trip converted timestamp: " << sinceEpoch.count() << std::endl;
}
