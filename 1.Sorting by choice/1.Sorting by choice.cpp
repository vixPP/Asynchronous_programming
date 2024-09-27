#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>

int find_minimum(const std::vector<int>& arr, int start, int end) 
{
    int min_index = start;
    for (int i = start + 1; i < end; ++i) 
    {
        if (arr[i] < arr[min_index]) 
        {
            min_index = i;
        }
    }
    return min_index;
}

void selection_sort(std::vector<int>& arr) 
{
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) 
    {
        std::promise<int> promise;
        std::future<int> future = promise.get_future();

        std::thread([&, i, n, promise = std::move(promise)]() mutable 
            {
            int min_index = find_minimum(arr, i, n);
            promise.set_value(min_index);
            }).detach(); 

        int min_index = future.get();

        std::swap(arr[i], arr[min_index]);
    }
}

int main() 
{
    std::vector<int> arr = { 210, 25, 12, 22, 11 };

    std::cout << "Original array: ";
    for (int num : arr) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    selection_sort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
} 