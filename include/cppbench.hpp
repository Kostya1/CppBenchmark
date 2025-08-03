#ifndef CPPBENCH_HPP
#define CPPBENCH_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <vector>
#include <mutex>
#include <cmath>

namespace cppbench {

struct Config {
    int iterations = 1;
    int threads = 1;
    bool auto_iterations = false;
    int min_total_ms = 200;
    int max_iters = 1000000;
};

void benchmark(const std::string& name, std::function<void()> func, const Config& config = {}) {
    using namespace std::chrono;

    int total_iterations = config.iterations;
    int thread_count = config.threads;

    if (thread_count <= 0) thread_count = 1;

    // Auto mode: dynamically determine iterations
    if (config.auto_iterations) {
        int iters = 1;
        double avg_time_us = 0.0;

        while (true) {
            auto start = high_resolution_clock::now();
            for (int i = 0; i < iters; ++i) func();
            auto end = high_resolution_clock::now();

            auto total_us = duration_cast<microseconds>(end - start).count();
            avg_time_us = total_us / static_cast<double>(iters);

            if (total_us >= config.min_total_ms * 1000 || iters >= config.max_iters) {
                total_iterations = iters;
                break;
            }

            iters = std::min(iters * 2, config.max_iters);
        }
    }

    int iterations_per_thread = total_iterations / thread_count;
    int remainder = total_iterations % thread_count;

    std::vector<std::thread> threads;
    std::mutex io_mutex;

    auto start = high_resolution_clock::now();

    for (int t = 0; t < thread_count; ++t) {
        int iters = iterations_per_thread + (t < remainder ? 1 : 0);
        threads.emplace_back([&func, iters]() {
            for (int i = 0; i < iters; ++i) func();
        });
    }

    for (auto& th : threads) th.join();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    double avg_time = duration / static_cast<double>(total_iterations);

    std::cout << "[CppBenchLite] " << name << " — " << avg_time
              << " µs avg (" << total_iterations << " runs, "
              << thread_count << " threads)\n";
}

} // namespace cppbench

#endif // CPPBENCH_HPP
