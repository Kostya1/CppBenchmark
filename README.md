# CppBenchLite

🧪 A lightweight, header-only C++ microbenchmarking library with optional multithreading and automatic iteration calibration.

## 🔧 Features

- Simple API: `cppbench::benchmark(...)`
- Optional multithreaded execution
- Auto mode: dynamically determines the optimal number of iterations
- No dependencies — pure C++17
- Easy to integrate into any project

## 📦 Installation

Just copy `include/cppbench.hpp` into your project.

No build steps or external libraries needed.

## 🚀 Example

```cpp
#include "cppbench.hpp"

void task() {
    // your code to benchmark
}

int main() {
    cppbench::Config cfg;
    cfg.auto_iterations = true;
    cfg.threads = 4;
    cfg.min_total_ms = 300;

    cppbench::benchmark("Auto-parallel benchmark", task, cfg);
}
