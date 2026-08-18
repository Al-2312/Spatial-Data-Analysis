# Spatial-Data-Analysis
Originally developed 3 year ago as a final project for intro to C++ course. this project has been completely rewritten and optimized as a modern C++23 application designed to parse, hash, and analyze over 1,000,000 multi-dimensional (2D and 3D) points. 

The goal of this updated project is to demonstrate low-level systems optimization, memory management, and microarchitectural profiling.

## Architecture and Optimizations

* **Bypassed Standard I/O** Utilized Linux `mmap` and `std::ispanstream` for zero-copy file reading, avoiding standard stream I/O overhead.

* **Zero-Allocation Parsing:** Replaced standard strings with `std::string_view` to extract data without triggering unnecessary heap/string allocations.

* **Modern Memory Views** Leveraged `std::views::zip` to combine multiple coordinate vectors into tuple views for fast, zero-copy reference reading.

* **Compile-Time Hashing:** Implemented a custom variadic template hashing functor utilizing `std::apply` to efficiently hash `std::tuple` structures within a `std::unordered_set`. 

## Profiling and Performance Metrics

The initial implementation suffered from severe memory and algorithmic bottlenecks. Parsing relied on dynamic string concatenation causing continuous heap reallocations, 2D frequency counting used an O(N²) nested loop resulting in billions of redundant instructions, and 3D frequency counting utilized pass-by-value `std::vector` copies inside a `std::map`, forcing heavy `libc` memory comparisons (`memcmp`) 

Using Linux `perf` (`stat`, `record --call-graph`), bottlenecks were identified. The data structures were subsequently refactored to utilize a Structure of Arrays (SoA) layout and `std::unordered_set`.

**Resulting Metrics:**
* Execution time was reduced from 20.8 seconds to 900 milliseconds (-O0) to 140 milliseconds (-O2) (>150x speedup).

* Total executed CPU instructions were reduced by approximately 211 billion.

## Potential Improvements
* **Flat C-Structs for Hashing:** Linux `perf` sampling indicated that roughly 27% of execution time was spent hashing `std::tuple` within the `std::unordered_set`. Replacing these tuples entirely with flattened custom structs would further reduce this overhead.

* **Dynamic Bucket Allocation** Pre-allocating std::unordered_set bucket sizes dynamically based on initial mmap file byte-size estimates to prevent rehashing

* **Algorithmic Distance Calculation** Implementing Convex Hull and Rotating Calipers algorithms to find the maximum distance between 2D points algorithmically, rather than relying on dataset-specific boundries.

## Build Instructions
### Prerequisites
* A Linux environment (requires `sys/mman.h` for memory mapping (i.e `mmap`).
* A compiler supporting C++23 perferably clang 18+

### Compilation
Compile with optimizations enabled:
```bash
clang++ -Wall -Wextra -Werror -std=c++23 -O2 -g newMain.cpp -o newmain
