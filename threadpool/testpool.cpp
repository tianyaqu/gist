#include <iostream>
#include <vector>
#include "threadpool.h"

using namespace std;


int main()
{
    ThreadPool pool(8);
    pool.start();

    auto result = pool.submit([](int answer) { return answer; }, 42);
    std::cout << result.get() << std::endl;

    std::vector< std::future<int> > results;
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.submit([i] {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';

    return 0;
}
