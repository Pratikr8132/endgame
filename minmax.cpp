#include <iostream>
// #include <vector>
#include <omp.h>
#include <climits>
using namespace std;
void min_reduction(int arr[], int n)
{
    int min_value = INT_MAX;
#pragma omp parallel for reduction(min : min_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}
void max_reduction(int arr[], int n)
{
    int max_value = INT_MIN;
#pragma omp parallel for reduction(max : max_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}
void sum_reduction(int arr[], int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}
void average_reduction(int arr[], int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / (n - 1) << endl;
}
int main()
{
    int *arr, n;
    cout << "\n enter total no of elements=>";
    cin >> n;
    arr = new int[n];
    cout << "\n enter elements=>";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);
}
// g++ -fopenmp program.cpp -o program
// ./program

//  enter total no of elements=>5

//  enter elements=>11
// 22
// 33
// 44
// 55
// Minimum value: 11
// Maximum value: 55
// Sum: 165
// Average: 41.25










































































































































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





//EXPLANTION OF THE CODE



// Let's break down the code line by line and explain each part, including the libraries used, the OpenMP directives, and how each function works:

// cpp
// Copy code
// #include <iostream>
// #include <omp.h>
// #include <climits>
// using namespace std;
// #include <iostream>: This header includes the standard input-output stream library, allowing you to use cout and cin for input-output operations.
// #include <omp.h>: This header includes the OpenMP library, which provides directives and functions for parallel programming.
// #include <climits>: This header includes constants for minimum and maximum values of various data types, such as INT_MAX and INT_MIN.
// Moving on to the function implementations:

// cpp
// Copy code
// void min_reduction(int arr[], int n)
// {
//     int min_value = INT_MAX;
// #pragma omp parallel for reduction(min : min_value)
//     for (int i = 0; i < n; i++)
//     {
//         if (arr[i] < min_value)
//         {
//             min_value = arr[i];
//         }
//     }
//     cout << "Minimum value: " << min_value << endl;
// }
// min_reduction is a function that calculates the minimum value in an array using OpenMP parallelization and reduction.
// #pragma omp parallel for reduction(min : min_value): This directive parallelizes the loop and performs a reduction operation to find the minimum value. Each thread maintains its local minimum, and then these local minima are combined to find the global minimum (min_value).
// Inside the loop, if an element is smaller than min_value, it updates min_value accordingly.
// Similarly, let's look at max_reduction, sum_reduction, and average_reduction functions:

// cpp
// Copy code
// void max_reduction(int arr[], int n)
// {
//     int max_value = INT_MIN;
// #pragma omp parallel for reduction(max : max_value)
//     for (int i = 0; i < n; i++)
//     {
//         if (arr[i] > max_value)
//         {
//             max_value = arr[i];
//         }
//     }
//     cout << "Maximum value: " << max_value << endl;
// }
// max_reduction calculates the maximum value in an array using OpenMP parallelization and reduction. It's similar to min_reduction but with the max reduction clause.
// cpp
// Copy code
// void sum_reduction(int arr[], int n)
// {
//     int sum = 0;
// #pragma omp parallel for reduction(+ : sum)
//     for (int i = 0; i < n; i++)
//     {
//         sum += arr[i];
//     }
//     cout << "Sum: " << sum << endl;
// }
// sum_reduction calculates the sum of elements in an array using OpenMP parallelization and reduction. The + reduction clause indicates addition.
// cpp
// Copy code
// void average_reduction(int arr[], int n)
// {
//     int sum = 0;
// #pragma omp parallel for reduction(+ : sum)
//     for (int i = 0; i < n; i++)
//     {
//         sum += arr[i];
//     }
//     cout << "Average: " << (double)sum / (n - 1) << endl;
// }
// average_reduction calculates the average of elements in an array using OpenMP parallelization and reduction. It first calculates the sum using a similar approach to sum_reduction and then divides by the number of elements (n - 1) to get the average.
// Lastly, the main function reads input, calls the reduction functions, and prints the results:

// cpp
// Copy code
// int main()
// {
//     int *arr, n;
//     cout << "\n enter total no of elements=>";
//     cin >> n;
//     arr = new int[n];
//     cout << "\n enter elements=>";
//     for (int i = 0; i < n; i++)
//     {
//         cin >> arr[i];
//     }
//     min_reduction(arr, n);
//     max_reduction(arr, n);
//     sum_reduction(arr, n);
//     average_reduction(arr, n);
// }
// The main function prompts the user to enter the number of elements and the elements themselves.
// It then calls each reduction function (min_reduction, max_reduction, sum_reduction, average_reduction) to compute and print the minimum, maximum, sum, and average values of the input array using OpenMP parallelization and reduction techniques.
// Overall, the code demonstrates how to leverage OpenMP directives for parallel reduction operations, making efficient use of multiple threads to compute aggregate values from an array concurrently.

