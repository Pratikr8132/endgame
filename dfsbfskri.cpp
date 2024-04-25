#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void parallelBFS(vector<int> adj[], int start, int n)
{

    vector<int> vis(n + 1, 0);
    queue<int> q;
    q.push(start);
    cout << "\nBFS of the given graph is: " << endl;
    while (!q.empty())
    {
        int top = q.front();
        q.pop();
        cout << top << " ";
        vis[top] = 1;
#pragma omp parallel for shared(adj, vis, q)
        for (auto neigh : adj[top])
        {
            if (vis[neigh] == 0)
            {
                q.push(neigh);
                vis[neigh] = 1;
            }
        }
    }
}

void parallelDFS(vector<int> adj[], vector<int> &vis, int start)
{
    cout << start << " ";
    vis[start] = 1;
#pragma omp parallel for shared(Adj, vis)
    for (auto neigh : adj[start])
    {
        if (vis[neigh] == 0)
        {
            parallelDFS(adj, vis, neigh);
            vis[neigh] = 1;
        }
    }
}

int main()
{
    int n;
    cout << "Enter the no of vertices in a graph: " << endl;
    cin >> n;
    int m;
    cout << "Enter the no of edges in a graph: " << endl;
    cin >> m;
    vector<int> adj[n + 1];
    cout << "Enter the  edges in a graph: " << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int start;
    cout << "Enter the starting node: " << endl;
    cin >> start;
    parallelBFS(adj, start, n);
    vector<int> vis(n + 1, 0);
    cout << "\nDFS of the given graph is:  " << endl;
    parallelDFS(adj, vis, start);
    return 0;
}
// g++ -fopenmp filename.cpp -o executable
// ./executable

//sample code--....




// Enter the no of vertices in a graph: 
// 6
// Enter the no of edges in a graph: 
// 5
// Enter the  edges in a graph: 
// 1 2
// 1 3
// 2 6
// 2 4
// 4 5
// Enter the starting node: 
// 1

// BFS of the given graph is: 
// 1 2 3 6 4 5 
// DFS of the given graph is:  
// 1 2 6 4 5 3 


























































































































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






// //EXPLANATION OF THE CODE


// Let's go through the code line by line and explain each part, including the libraries used, how the code works, and the parallelism achieved using OpenMP directives.

// First, let's look at the libraries used:

// cpp
// Copy code
// #include <bits/stdc++.h>
// #include <omp.h>
// #include <bits/stdc++.h>: This header is not a standard C++ header but is commonly used in competitive programming environments as it includes most of the standard library headers (`
// iostream, vector, queue`, etc.) in one go. It's convenient for quickly setting up a program without worrying about individual headers.

// #include <omp.h>: This includes the OpenMP header, which is used for parallel programming. OpenMP stands for Open Multi-Processing and provides directives and functions for shared-memory multiprocessing.
// Now let's break down the code line by line:

// cpp
// Copy code
// using namespace std;
// This line brings all the symbols in the std namespace into the current scope, making it unnecessary to prefix standard library functions and types with std::.
// Moving on to the functions:

// cpp
// Copy code
// void parallelBFS(vector<int> adj[], int start, int n)
// {
//     vector<int> vis(n + 1, 0);
//     queue<int> q;
//     q.push(start);
//     cout << "\nBFS of the given graph is: " << endl;
//     while (!q.empty())
//     {
//         int top = q.front();
//         q.pop();
//         cout << top << " ";
//         vis[top] = 1;
// #pragma omp parallel for shared(adj, vis, q)
//         for (auto neigh : adj[top])
//         {
//             if (vis[neigh] == 0)
//             {
//                 q.push(neigh);
//                 vis[neigh] = 1;
//             }
//         }
//     }
// }
// parallelBFS is a function that performs a parallelized Breadth-First Search (BFS) traversal of a graph represented using an adjacency list (vector<int> adj[]).
// It initializes a vis vector to keep track of visited nodes, and a queue q for BFS traversal.
// Inside the while loop, it processes nodes in the queue, marks them as visited, and pushes their unvisited neighbors into the queue.
// #pragma omp parallel for shared(adj, vis, q): This directive parallelizes the loop that iterates over the neighbors of the current node. It shares the adjacency list (adj), visited vector (vis), and queue (q) among threads to perform the BFS traversal concurrently.
// Next, the parallelDFS function:

// cpp
// Copy code
// void parallelDFS(vector<int> adj[], vector<int> &vis, int start)
// {
//     cout << start << " ";
//     vis[start] = 1;
// #pragma omp parallel for shared(adj, vis)
//     for (auto neigh : adj[start])
//     {
//         if (vis[neigh] == 0)
//         {
//             parallelDFS(adj, vis, neigh);
//             vis[neigh] = 1;
//         }
//     }
// }
// parallelDFS performs a parallelized Depth-First Search (DFS) traversal of the graph.
// It marks the starting node as visited and recursively explores its neighbors in parallel using OpenMP directives.
// #pragma omp parallel for shared(adj, vis): This directive parallelizes the loop that traverses the neighbors of the current node during DFS. It shares the adjacency list (adj) and visited vector (vis) among threads for concurrent traversal.
// Finally, the main function:

// cpp
// Copy code
// int main()
// {
//     // Code to read graph inputs and perform parallel BFS and DFS
// }
// In main, the user is prompted to enter the number of vertices, edges, edge details, and the starting node.
// The adj vector array is filled with the graph's adjacency list representation.
// Parallel BFS (parallelBFS) and DFS (parallelDFS) are called to traverse the graph concurrently using OpenMP parallelization.
// Overall, the code demonstrates how to implement parallel BFS and DFS traversal using OpenMP directives for shared-memory multiprocessing. The parallelization allows for faster traversal of large graphs by utilizing multiple threads to explore nodes simultaneously.