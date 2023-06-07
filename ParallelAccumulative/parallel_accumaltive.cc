#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>


#define MIN_BLOCK_SIZE 1000

template<typename iterator, typename T> 
void accumulate(iterator start, iterator end, T &ref) {
    ref = std::accumulate(start, end, 0);
}

template<typename iterator, typename T>
T parallel_accumulte(iterator start, iterator end, T &ref) {

    // First Compute total threads to run on base of
    // input given
    auto input_size = std::distance(start, end);
    int min_threads = input_size / MIN_BLOCK_SIZE;
    int core_available = std::thread::hardware_concurrency();
    auto threads_allowed = std::min(min_threads, core_available);
    auto block_size = (input_size + 1) / threads_allowed;

    // Create vectors to store data and threads running
    std::vector<std::thread> threads(threads_allowed - 1);
    std::vector<T> results(threads_allowed);

    iterator last;

    for(int i=0; i<threads_allowed-1; i++) {
        last = start;
        std::advance(last, block_size);
        threads[i] = std::thread(accumulate<iterator, T>, start, last, std::ref(results[i]));
        start = last;
    }
    results[threads_allowed - 1] = std::accumulate(start, end, 0);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(), results.end(), ref);

}

int main() {
    const int size = 10000;
    int* arr = new int[size];
    int ref = 0;
    srand(0);
    for(int i = 0; i < size; i++) {
        arr[i] = rand() % 10;
    }
    auto ans = parallel_accumulte<int*, int>(arr, arr + size, ref);
    std::cout << "Ans is : " << ans <<  std::endl;
    std::cout << "calling from main" << std::endl;
    return 0;
}