#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

template<typename Iterator, typename Function>
void parallel_for_each(Iterator begin, Iterator end, Function func) 
{
    auto length = std::distance(begin, end);
    if (length <= 1000) 
    { 
        std::for_each(begin, end, func);
    }
    else 
    {
        auto mid = begin + length / 2;

        std::thread left_thread(parallel_for_each<Iterator, Function>, begin, mid, func);
        std::thread right_thread(parallel_for_each<Iterator, Function>, mid, end, func);

        left_thread.join();
        right_thread.join();
    }
}

int main() 
{
    std::vector<int> vec(1500);
    std::iota(vec.begin(), vec.end(), 1); 

    auto print = [](int n) 
    {
      std::cout << n << " ";
    };

    parallel_for_each(vec.begin(), vec.end(), print);

    return 0;
}
