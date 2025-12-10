

# ⚡ OpenMP Matrix Multiplication Benchmark

A C program that demonstrates the raw power of **parallel computing** by benchmarking Matrix Multiplication. It compares the execution time of a standard serial implementation against a parallelized version using the **OpenMP API**.

-----

## 🚀 Overview

Matrix multiplication is a computationally intensive operation with a complexity of $O(N^3)$. This project allows you to visualize the performance gains achieved by utilizing multi-core processors.

**The program performs the following:**

  * ✅ **Generates** two `N x N` matrices filled with user-defined values.
  * 🐌 **Calculates** the product using a single thread (Sequential).
  * ⚡ **Calculates** the product using multiple threads (Parallel via OpenMP).
  * 📊 **Compares** execution times and calculates the exact speedup factor.

-----

## 🧐 Why 1000x1000?

You might wonder why this benchmark uses a fixed size of **1000x1000** rather than a simple 3x3 or 4x4 matrix.

> **Parallel computing is not magic; it comes with a cost.** \> Spawning threads, distributing tasks, and synchronizing memory (overhead) takes time.

| Matrix Size | Behavior |
| :--- | :--- |
| **Small (e.g., 3x3)** | The actual calculation is so fast that the time spent *managing* the threads is longer than the math itself. |
| **Large (1000x1000)** | Requires **1 billion** multiplications and additions. This massive workload justifies the overhead, allowing parallelism to shine. |

-----

## 🛠️ Prerequisites

You need a C compiler that supports OpenMP (like GCC).

  * **Linux (Ubuntu/Debian):**
    ```bash
    sudo apt update
    sudo apt install build-essential
    ```
  * **Windows (MinGW):** Ensure you have MinGW installed with pthreads/OpenMP support.

-----

## 💻 How to Run

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/anmol-goyal7/your-repo-name.git
    cd your-repo-name
    ```

2.  **Compile the code:**
    *Note: You must include the `-fopenmp` flag.*

    ```bash
    gcc -o matrix_test main.c -fopenmp
    ```

3.  **Execute:**

    ```bash
    ./matrix_test
    ```

-----

## 📊 Sample Output

When running on a Quad-core processor, you might see results like this:

```text
Without OpenMP: 4.250000 seconds
With OpenMP:    1.120000 seconds
----------------------------------------
Speedup:        3.79x faster
Time saved:     3.130000 seconds (73.6%)
```

-----

## 🧩 The "Secret Sauce"

The core logic that enables parallelism is this simple OpenMP pragma:

```c
// The magic line that splits the work across threads
#pragma omp parallel for private(i, j, k) shared(mat1, mat2, result)
for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
        // ... matrix logic
    }
}
```

-----


  * Freshman, B.Tech CSE (SWE) @ SRM University
  * [GitHub Profile](https://www.google.com/search?q=https://github.com/anmol-goyal7)
