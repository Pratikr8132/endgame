#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;
void bubble(int *, int);
void swap(int &, int &);
void bubble(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;
#pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}
void swap(int &a, int &b)
{
    int test;
    test = a;
    a = b;
    b = test;
}
int main()
{
    int *a, n;
    cout << "\n enter total no of elements=>";
    cin >> n;
    a = new int[n];
    cout << "\n enter elements=>";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    bubble(a, n);
    cout << "\n sorted array is=>\n";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }
    return 0;
}
// g++ -fopenmp filename.cpp -o executable
// ./executable
// enter number of elements ... then add one then enter and like that






















































































































































































// EXPLANATION

// Let's break down the code line by line and explain each part:

// cpp
// Copy code
// #include <iostream>
// #include <stdlib.h>
// #include <omp.h>
// using namespace std;
// #include <iostream>: This includes the input-output stream header, allowing you to use standard input-output operations like cout and cin.
// #include <stdlib.h>: This includes the standard library header, which provides functions for memory allocation, process control, conversions, and others.
// #include <omp.h>: This includes the OpenMP header, which is used for parallel programming. OpenMP stands for Open Multi-Processing, and it's a library that supports multi-platform shared-memory multiprocessing programming.
// cpp
// Copy code
// void bubble(int *, int);
// void swap(int &, int &);
// These are function prototypes. They declare two functions: bubble and swap. The bubble function is used for bubble sort, and swap is a helper function for swapping two integers.
// cpp
// Copy code
// void bubble(int *a, int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         int first = i % 2;
// #pragma omp parallel for shared(a, first)
//         for (int j = first; j < n - 1; j += 2)
//         {
//             if (a[j] > a[j + 1])
//             {
//                 swap(a[j], a[j + 1]);
//             }
//         }
//     }
// }
// This is the implementation of the bubble sort algorithm. It takes an integer array a and its size n as parameters.
// Inside the bubble function, there's a nested loop structure for the bubble sort algorithm. The outer loop iterates from i = 0 to i = n - 1.
// int first = i % 2;: This line calculates whether the starting index of the inner loop should be 0 or 1 based on the current iteration of the outer loop. It alternates between starting at index 0 and index 1.
// #pragma omp parallel for shared(a, first): This line is an OpenMP directive. It tells the compiler to parallelize the following loop (for (int j = first; j < n - 1; j += 2)) using multiple threads. The shared(a, first) clause specifies that the variables a and first are shared among all threads.
// The inner loop (for (int j = first; j < n - 1; j += 2)) performs the actual bubble sort comparisons and swaps elements if necessary.
// cpp
// Copy code
// void swap(int &a, int &b)
// {
//     int test;
//     test = a;
//     a = b;
//     b = test;
// }
// This is the implementation of the swap function, which takes two integer references (int &a and int &b) and swaps their values.
// cpp
// Copy code
// int main()
// {
//     int *a, n;
//     cout << "\n enter total no of elements=>";
//     cin >> n;
//     a = new int[n];
//     cout << "\n enter elements=>";
//     for (int i = 0; i < n; i++)
//     {
//         cin >> a[i];
//     }
//     bubble(a, n);
//     cout << "\n sorted array is=>\n";
//     for (int i = 0; i < n; i++)
//     {
//         cout << a[i] << endl;
//     }
//     return 0;
// }
// This is the main function, which is the entry point of the program.
// It first prompts the user to enter the total number of elements (n) and dynamically allocates memory for an integer array a of size n.
// Then, it prompts the user to enter the elements of the array.
// After inputting the elements, it calls the bubble function to sort the array.
// Finally, it prints the sorted array.
// Regarding the compilation and execution commands mentioned at the end of the code:

// g++ -fopenmp filename.cpp -o executable: This command compiles the C++ code (filename.cpp) with OpenMP support (-fopenmp) and creates an executable named executable.
// ./executable: This command runs the compiled executable, allowing you to interact with the program as described above.



// OPENMP---

// WHAT IS OPENMP EXPLAIN THAT CONCEPT IN DEPTH
// ChatGPT
// OpenMP (Open Multi-Processing) is an API (Application Programming Interface) that supports multi-platform shared-memory multiprocessing programming in C, C++, and Fortran. It is designed to simplify parallel programming, making it easier to write code that can run efficiently on multicore systems and shared-memory multiprocessor architectures. Here's a more in-depth explanation of OpenMP:

// Parallelism:
// OpenMP allows you to create parallel regions in your code. A parallel region is a block of code that can be executed by multiple threads simultaneously.
// Threads are separate paths of execution within a process. Each thread has its own stack and registers but shares memory with other threads within the same process.
// Directives:
// OpenMP uses directives, which are special annotations in the code that guide the compiler on how to parallelize certain sections of code.
// Directives are typically prefixed with #pragma omp in C/C++ or specified using compiler flags in Fortran.
// Data Scope:
// OpenMP provides control over the scope of data in parallel regions. You can specify whether variables are shared (accessible to all threads), private (separate for each thread), or thread-local.
// This control helps manage data consistency and avoid race conditions (situations where multiple threads access and potentially modify shared data concurrently).
// Work Sharing Constructs:
// OpenMP supports work sharing constructs like parallel for, parallel sections, and task constructs.
// parallel for divides loop iterations among threads, allowing them to work on different parts of the loop in parallel.
// parallel sections divides code into sections that can be executed concurrently by different threads.
// task constructs define tasks that can be executed asynchronously, providing finer-grained parallelism.
// Synchronization:
// OpenMP provides synchronization mechanisms to coordinate the execution of threads.
// Directives like critical, atomic, and barrier ensure proper synchronization, preventing data races and ensuring correct program behavior.
// Environment Variables and API Functions:
// OpenMP allows you to control runtime behavior through environment variables that adjust parameters such as the number of threads to use.
// It also provides API functions that enable programmatic control over parallelism, thread management, and synchronization.
// Portability:
// OpenMP is designed to be portable across different platforms and compilers.
// It adheres to a standard specification, allowing developers to write parallel code that can be compiled and executed on various systems without major modifications.
// Performance Considerations:
// While OpenMP simplifies parallel programming, achieving optimal performance often requires considerations such as load balancing, minimizing synchronization overhead, and maximizing locality of data access.
// Profiling tools and compiler optimizations can help analyze and improve the performance of OpenMP parallelized code.
// In summary, OpenMP is a powerful tool for parallel programming, providing a high-level interface that abstracts many complexities of parallel execution. It enables developers to write scalable and efficient parallel code for shared-memory systems, contributing to improved performance and utilization of modern multicore processors.