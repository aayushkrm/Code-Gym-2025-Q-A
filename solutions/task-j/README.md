# Task J: Grid Restoration with Path Constraints

## Problem Description

*This problem description is inferred from the solution code.*

You are given an `n x m` grid of integers, `a`, and a path from the top-left cell (1,1) to the bottom-right cell (n,m) consisting only of 'Down' and 'R'ight moves. The goal is to find a new grid, `b`, that satisfies the following conditions:

1.  **Path Modification:** The values of cells on the given path may be changed. The values of cells *not* on the path must remain the same as in the original grid `a`.
2.  **Zero-Sum Rows:** The sum of all elements in each row of the final grid `b` must be 0.
3.  **Zero-Sum Columns:** The sum of all elements in each column of the final grid `b` must be 0.

The problem guarantees that a unique solution for the values on the path exists.

## Solution Approach

This complex problem is elegantly solved by modeling it as a system of linear equations and using a custom solver. The core idea is to introduce "potentials" for each row and column.

1.  **Potential-Based Model:**
    *   Let's assign a potential `u_i` to each row `i` and a potential `v_j` to each column `j`.
    *   The problem can be modeled by setting the final value of a cell `(i, j)` on the path to be `b_ij = u_i - v_j`. This structure is common in problems involving grid constraints.
    *   Our goal is to find the values of these `n+m` potentials.

2.  **Forming Linear Equations:**
    *   The zero-sum constraints provide the equations. For each row `i`, the sum of its elements must be 0:
        `Sum(b_ik for k not in path) + Sum(u_i - v_k for k in path) = 0`
    *   This can be rewritten. Let `S_row[i]` be the initial sum of row `i`. The sum of non-path elements is `S_row[i] - Sum(a_ik for k in path)`. The equation becomes a linear equation in terms of the potentials. A similar equation is derived for each column.
    *   The code simplifies this by setting up equations of the form:
        *   For each row `i`: `|P_i|*u_i - Sum(v_j for j in P_i) = -S_row[i]`, where `P_i` is the set of columns `j` such that `(i,j)` is on the path.
        *   For each column `j`: `Sum(u_i for i in P_j) - |P_j|*v_j = -S_col[j]`, where `P_j` is the set of rows `i` such that `(i,j)` is on the path.

3.  **Graph Representation:**
    *   This system of equations can be represented by a bipartite graph `G_P` where one set of nodes represents the rows and the other represents the columns. An edge exists between row `i` and column `j` if the cell `(i,j)` is on the path.
    *   It is a known property that for a path of this type, the resulting graph `G_P` is a tree. This is crucial because it means the equations are not redundant and a unique solution (up to an additive constant) exists.

4.  **Solving the System:**
    *   The system has `n+m` variables (the potentials) but only `n+m-1` independent equations (since the graph is a tree). To get a unique solution, we can fix one potential. The code sets `u_0 = 0`.
    *   With one potential known, the system can be solved. The code implements a custom solver that works like a Breadth-First Search (BFS) or a topological sort on the equation dependencies.
    *   It maintains a queue of equations that have only one remaining unknown variable. When an equation is solved, the value of the newly found potential is substituted into all other equations it appears in. This might, in turn, reduce the unknown count in other equations to 1, adding them to the queue.
    *   This process continues until all potentials are found.

5.  **Constructing the Final Grid:**
    *   Once all potentials `u_i` and `v_j` are known, the final grid `b` is constructed. It starts as a copy of `a`.
    *   Then, for each cell `(i,j)` on the path, its value is overwritten with the calculated `b_ij = u_i - v_j`.

This sophisticated approach correctly and efficiently solves the problem by transforming it into a well-understood mathematical structure.
