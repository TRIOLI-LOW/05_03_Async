#include <iostream>
#include <algorithm>
#include <vector>
#include <future>
#include <thread>
#include <iostream>

template <typename It, typename Func>
void main_process(It begin, It end, Func func) {
    std::for_each(begin, end, func);
}

template <typename It, typename Func>
void async_process(It first, It last, Func func) {
    const auto size = std::distance(first, last);
    const auto part = 10;// пороговое значение
    if (size <= part) {
        main_process (first, last, func);
    }
    else {
        It mid = std::next(first, size / 2);
        std::shared_future<void> future = std::async(std::launch::async, async_process<It, Func>, first, mid, func);

        async_process(mid, last, func);
        
        future.get();
    }
}


int main()
{
    std::vector<int> numbers(1000, 5);

    async_process(numbers.begin(), numbers.end(), [](int num) {
        std::cout << num << " ";
        });

}
