#include <thread>

int main()
{
    using namespace std::chrono_literals;
    while(1)
    {
        std::this_thread::sleep_for(1s);
    }
}
