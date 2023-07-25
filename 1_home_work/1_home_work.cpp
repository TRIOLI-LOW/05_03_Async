#include <thread>
#include <iostream>
#include <future>
#include <vector>


void async_find(const std::vector<int>& arr, int start, int end, std::promise<int>& prom) {
    int min = start;
    for (int i = start + 1; i < end; ++i) {
        if (arr[i] < arr[min]) {
            min = i;
        }
    }
    prom.set_value(min);
}

void sort_arr(std::vector<int>& arr) {
    int size = arr.size();
    for (int i = 0; i < size; ++i) {
        std::promise<int> prom;
        std::future<void> fut = std::async(async_find, arr, i, size, std::ref(prom));;
        
        int min = prom.get_future().get();

        if (min != i) {

            std::swap(arr[i], arr[min]);
        }

    }
}


int main()
{
    std::vector<int> arr = { 64, 25, 12, 22, 11, 87, 152, 24, 65, 39, 21, 14 };
    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }

   sort_arr(arr);

    std::cout << "\nSorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
