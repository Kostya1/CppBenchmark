#include "cppbench.hpp"
#include <vector>
#include <algorithm>

void test_sort() {
    std::vector<int> v(10000);
    std::generate(v.begin(), v.end(), rand);
    std::sort(v.begin(), v.end());
}


int main() {
    cpp::bench::benchmark("std::sort", test_sort, 5);
}
