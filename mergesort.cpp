#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;
void mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);
void mergesort(int a[], int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                mergesort(a, i, mid);
            }
#pragma omp section
            {
                mergesort(a, mid + 1, j);
            }
        }
        merge(a, i, mid, mid + 1, j);
    }
}
void merge(int a[], int i1, int j1, int i2, int j2)
{
    int temp[1000];
    int i, j, k;
    i = i1;
    j = i2;
    k = 0;
    while (i <= j1 && j <= j2)
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }
    while (i <= j1)
    {
        temp[k++] = a[i++];
    }
    while (j <= j2)
    {
        temp[k++] = a[j++];
    }
    for (i = i1, j = 0; i <= j2; i++, j++)
    {
        a[i] = temp[j];
    }
}
int main()
{
    int *a, n, i;
    cout << "\n enter total no of elements=>";
    cin >> n;
    a = new int[n];
    cout << "\n enter elements=>";
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    mergesort(a, 0, n - 1);
    cout << "\n sorted array is=>";
    for (i = 0; i < n; i++)
    {
        cout << "\n"
             << a[i];
    }
    return 0;
}
// g++ -fopenmp filename.cpp -o executable
// ./executable
// enter number of elements ... then add one then enter and like that

































































































































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







// //EXPLANATION OF CODE--->

// Let's break down the code line by line and explain each part in detail, including the libraries used and how the code works:

// cpp
// Copy code
// #include <iostream>
// #include <stdlib.h>
// #include <omp.h>
// using namespace std;
// #include <iostream>: This includes the input-output stream header, allowing you to use standard input-output operations like cout and cin.
// #include <stdlib.h>: This includes the standard library header, which provides functions like memory allocation (malloc, calloc), process control (exit), and conversions (atoi, atof).
// #include <omp.h>: This includes the OpenMP header, which is used for parallel programming. OpenMP stands for Open Multi-Processing and provides directives and functions for shared-memory multiprocessing.
// Next, we have function prototypes for mergesort and merge:

// cpp
// Copy code
// void mergesort(int a[], int i, int j);
// void merge(int a[], int i1, int j1, int i2, int j2);
// These lines declare the functions mergesort and merge. mergesort is a recursive function used for performing merge sort, while merge is a helper function for merging two sorted subarrays.
// Moving on to the mergesort function implementation:

// cpp
// Copy code
// void mergesort(int a[], int i, int j)
// {
//     int mid;
//     if (i < j)
//     {
//         mid = (i + j) / 2;
// #pragma omp parallel sections
//         {
// #pragma omp section
//             {
//                 mergesort(a, i, mid);
//             }
// #pragma omp section
//             {
//                 mergesort(a, mid + 1, j);
//             }
//         }
//         merge(a, i, mid, mid + 1, j);
//     }
// }
// This function recursively sorts an array a between indices i and j using the merge sort algorithm.
// The if (i < j) condition checks if the array has more than one element, indicating the need for sorting.
// mid = (i + j) / 2; calculates the midpoint of the array.
// #pragma omp parallel sections creates parallel sections, allowing the recursive calls to mergesort to run concurrently in different threads.
// #pragma omp section specifies individual sections that can run in parallel.
// After the parallel sections, the merge function is called to merge the sorted subarrays.
// Now, let's look at the merge function:

// cpp
// Copy code
// void merge(int a[], int i1, int j1, int i2, int j2)
// {
//     int temp[1000];
//     int i, j, k;
//     i = i1;
//     j = i2;
//     k = 0;
//     while (i <= j1 && j <= j2)
//     {
//         if (a[i] < a[j])
//         {
//             temp[k++] = a[i++];
//         }
//         else
//         {
//             temp[k++] = a[j++];
//         }
//     }
//     while (i <= j1)
//     {
//         temp[k++] = a[i++];
//     }
//     while (j <= j2)
//     {
//         temp[k++] = a[j++];
//     }
//     for (i = i1, j = 0; i <= j2; i++, j++)
//     {
//         a[i] = temp[j];
//     }
// }
// This function merges two sorted subarrays within the array a. The subarrays are specified by their starting and ending indices (i1, j1, i2, j2).
// It uses a temporary array temp for merging.
// The merging process involves comparing elements from both subarrays and placing them in temp in sorted order.
// Finally, it copies the merged elements back into the original array a.
// Lastly, we reach the main function:

// cpp
// Copy code
// int main()
// {
//     int *a, n, i;
//     cout << "\n enter total no of elements=>";
//     cin >> n;
//     a = new int[n];
//     cout << "\n enter elements=>";
//     for (i = 0; i < n; i++)
//     {
//         cin >> a[i];
//     }
//     mergesort(a, 0, n - 1);
//     cout << "\n sorted array is=>";
//     for (i = 0; i < n; i++)
//     {
//         cout << "\n" << a[i];
//     }
//     return 0;
// }
// The main function prompts the user to enter the total number of elements (n) and then dynamically allocates memory for an integer array a of size n.
// It reads the elements of the array from the user.
// The mergesort function is called to sort the array.
// Finally, the sorted array is displayed.
// The code utilizes OpenMP for parallelism in the mergesort function, allowing for concurrent execution of recursive calls to mergesort, which speeds up the sorting process on multicore systems.