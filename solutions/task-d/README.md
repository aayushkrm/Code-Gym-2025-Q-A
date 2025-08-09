# Task D: Optimal Bidirectional Corridor

## Problem Description

*This problem description is inferred from the solution code.*

You are given a directed graph with `n` nodes and `n-1` one-way corridors (edges). You are also given `q` queries, each asking if a path exists from a starting node `x` to an ending node `y`.

Your task is to select exactly one of the `n-1` corridors and make it bidirectional. The goal is to choose the corridor that, when made bidirectional, maximizes the number of "YES" answers to the `q` queries.

The output should be the 1-based index of the chosen corridor, followed by the "YES" or "NO" result for each query in the optimally modified graph.

## Solution Approach

The solution employs a brute-force strategy over the corridors, which is feasible given the constraints of the problem.

1.  **Graph Representation:** The graph is represented using an adjacency list (`vector<vector<int>>`), where `graph[i]` stores a list of nodes reachable from node `i`. The initial `n-1` corridors are read and stored.

2.  **Iterating Through Corridors:** The core of the solution is a loop that iterates through each of the `n-1` corridors. In each iteration, it simulates making that corridor bidirectional.
    *   **Temporary Modification:** For a corridor from `a` to `b`, a reverse edge from `b` to `a` is temporarily added to the graph's adjacency list.
    *   **Evaluating Queries:** With the modified graph, the solution iterates through all `q` queries. For each query `(x, y)`, it checks if a path exists from `x` to `y`.
    *   **Path Checking:** The path existence check is done using a Breadth-First Search (BFS) algorithm, implemented in the `hasPath` function. BFS is a standard way to find if a path exists between two nodes in an unweighted graph. It uses a queue and a `visited` array to explore the graph layer by layer.
    *   **Counting and Comparing:** The number of queries satisfied (where a path exists) is counted for the current temporarily modified graph. This count is compared with the maximum count found so far. If the current choice of corridor yields a higher count, it is stored as the new best choice, and the results for each query are saved.
    *   **Reverting the Change:** After evaluating a corridor, the temporarily added reverse edge is removed to restore the graph to its state before the next iteration.

3.  **Output:** After checking all corridors, the solution prints the index of the best corridor found and the corresponding "YES" or "NO" results for each query.

This approach has a time complexity of O(N * Q * (N + M)), where N is the number of nodes and M is the number of edges. Given N and M are of similar order, it's roughly O(N*Q*N). This is computationally intensive but can pass if the constraints on N and Q are not too large.
