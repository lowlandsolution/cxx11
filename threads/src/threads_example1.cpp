#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <functional>

class Runnable
{
public:
    Runnable(int z) : m_z(z) { }

    // Main thread loop
    void mainLoop(int& x, int y)
    {

        while (x < 10)
        {

            // Mutual exclusion
            {
                std::lock_guard<std::mutex> guard(lock);
                std::cout << "loop " << y << ": "
                          << x << " " << m_z << std::endl;
                x++;
            }

            // Delay thread
            std::this_thread::sleep_for(std::chrono::seconds(2));

        }

    }

    // Make this static and public so all 3 threads can use it
    static std::mutex lock;

private:

    // Private data member to prove that yes, the Runnable object
    // is having its mainLoop function executed
    int m_z;

};

// Must define the lock object outside of the class declaration
std::mutex Runnable::lock;


// Use both bind and lambda function to start threads.
int main(int argc, char** argv)
{
    Runnable r(999);
    int x = 1;
    int y = 2;
    int z = 3;

    // Bind arguments in order to comply with the thead start
    // function prototype.  Pass x by reference so it can be modified
    // in the thread's main loop.  If std::ref() is not used, bind
    // copies or moves x instead of passing by reference.
    std::thread t1(std::bind(&Runnable::mainLoop, r, std::ref(x), y));

    // Use a lambda function to comply with the thread start
    // function prototype.  Capture x by reference so it can passed
    // to main loop by reference and modified in the thread's main loop.
    std::thread t2(
        [&r, &x, z] { r.mainLoop(x, z); }
    ); 

    while (x < 10) {

        // Mutual exclusion
        {
            std::lock_guard<std::mutex> guard(Runnable::lock);
            std::cout << "main loop " << x << std::endl;
        }

        // Delay thread
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    std::cout << "Waiting for threads to complete..." << std::endl;

    // Wait for threads to complete.
    t1.join();
    t2.join();

    return 0;
}

