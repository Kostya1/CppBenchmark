#include <vector>
#include <algorithm>

#include "cppbench.hpp"

void task() {
    std::vector<int> v(500);
    std::generate(v.begin(), v.end(), rand);
    std::sort(v.begin(), v.end());
}

int main() {
    cppbench::Config cfg;
    cfg.auto_iterations = true;
    cfg.threads = 4;
    cfg.min_total_ms = 300;

    cppbench::benchmark("Parallel auto-benchmark sort", task, cfg);
}
