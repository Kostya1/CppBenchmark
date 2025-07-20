#ifndef CPPBENCH_HPP
#define CPPBENCH_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <functional>

namespace cpp::bench
{

void benchmark(const std::string& name, std::function<void()> func, int iterations = 1) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        func();
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    std::cout << "[CppBench] " << name << ": "
              << (duration / static_cast<double>(iterations)) << " micros avg ("
              << iterations << " runs)\n";
}

}

#endif // CPPBENCH_HPP
