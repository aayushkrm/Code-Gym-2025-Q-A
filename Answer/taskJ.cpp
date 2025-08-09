#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <map>
#include <vector>
#include <queue> // Use std::queue for the BFS-like substitution solver

using namespace std;

// Use long long for grid values and potentials to handle potentially large values
// up to 10^15, as specified in the output format constraints.
typedef long long ll;

// Function to solve a single test case
void solve() {
    int n, m;
    cin >> n >> m; // Read grid dimensions (number of rows n, number of columns m)
    string s;
    cin >> s; // Read path string (sequence of 'D' down and 'R' right moves)

    // Read grid values and compute initial row and column sums
    vector<vector<ll>> a(n, vector<ll>(m)); // Stores the initial grid values
    vector<ll> S_row(n, 0); // S_row[i] stores the sum of elements in row i (0-based)
    vector<ll> S_col(m, 0); // S_col[j] stores the sum of elements in column j (0-based)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            S_row[i] += a[i][j];
            S_col[j] += a[i][j];
        }
    }

    // Determine the coordinates of cells on the path (0-based indices)
    vector<pair<int, int>> path_cells;
    int r = 0, c = 0; // Start at (0, 0) which corresponds to (1,1) in 1-based indexing
    path_cells.push_back({r, c}); // Add starting cell (0,0) to the path
    // Iterate through the path string s to find all cells on the path
    for (char move : s) {
        if (move == 'D') {
            r++; // Move down increases row index
        } else { // move == 'R'
            c++; // Move right increases column index
        }
        path_cells.push_back({r, c}); // Add the new cell to the path
    }
    // The path has n+m-1 cells in total.

    // We model the problem using potentials u_i for rows and v_j for columns.
    // For a cell (i,j) on the path, its final value b_ij will be u_i - v_j.
    // This leads to a system of linear equations derived from the row/column sum constraints.
    // We assume the target row/column sum X is 0, which simplifies the equations.
    // The system involves N row potentials (u_0..u_{n-1}) and M column potentials (v_0..v_{m-1}).

    // Let R'_i = S_row[i] and C'_j = S_col[j] be the initial sums.
    vector<ll> R_prime = S_row;
    vector<ll> C_prime = S_col;

    // Set up the system of linear equations.
    // There are N+M variables (potentials u_i and v_j).
    // We represent rows as nodes 0 to n-1, and columns as nodes n to n+m-1.
    int num_vars = n + m;
    vector<ll> potentials(num_vars); // Stores the calculated potential values u_i and v_j
    vector<bool> potential_known(num_vars, false); // Tracks which potentials have been solved

    // Build the bipartite graph G_P corresponding to the path.
    // Nodes are rows and columns involved in the path.
    // An edge exists between row node i and column node n+j if cell (i,j) is on the path.
    // This graph G_P is known to be a tree.
    vector<vector<int>> adj(num_vars); // Adjacency list for G_P
    vector<int> degree_in_path(num_vars, 0); // Stores the degree of each node in G_P
                                            // degree[i] = |P_i| = number of path cells in row i
                                            // degree[n+j] = |P_j| = number of path cells in column j

    // Populate adjacency list and degrees based on path cells
    for(const auto& p : path_cells) {
        int r_idx = p.first; // 0-based row index
        int c_idx = p.second; // 0-based col index
        int u_node_idx = r_idx;      // Node index for row i is i
        int v_node_idx = n + c_idx; // Node index for column j is n+j

        // Add edge between u_node_idx and v_node_idx if not already present.
        // Check is technically redundant as path cells are unique, but safe.
        bool found = false;
        for(int neighbor : adj[u_node_idx]){
            if(neighbor == v_node_idx) { found = true; break;}
        }
        if (!found) {
             adj[u_node_idx].push_back(v_node_idx);
             adj[v_node_idx].push_back(u_node_idx);
             // Increment degree for both nodes connected by this edge
             degree_in_path[u_node_idx]++;
             degree_in_path[v_node_idx]++;
        }
    }

    // Store equations implicitly for the substitution solver.
    // We use maps to store coefficients for non-zero terms.
    vector<map<int, ll>> eq_coeffs(num_vars); // eq_coeffs[k] maps variable index -> coefficient in equation k
    vector<ll> eq_const(num_vars); // eq_const[k] stores the constant term for equation k

    // Set up equation for row i (node index i): |P_i|*u_i - sum(v_j for j in P_i) = -R'_i
    // |P_i| is degree_in_path[i]. sum(v_j) involves neighbours in G_P.
    for(int i=0; i<n; ++i) {
        if (degree_in_path[i] > 0) { // Only create equations for rows that intersect the path
            eq_coeffs[i][i] = degree_in_path[i]; // Coefficient for u_i is degree |P_i|
            for(int neighbor_idx : adj[i]) { // Neighbors are v_j nodes (indices n+j)
                eq_coeffs[i][neighbor_idx] = -1; // Coefficient for v_j is -1
            }
            eq_const[i] = -R_prime[i]; // Constant term is -S_row[i]
        }
    }
    // Set up equation for column j (node index n+j): sum(u_i for i in P_j) - |P_j|*v_j = -C'_j
    // |P_j| is degree_in_path[n+j]. sum(u_i) involves neighbours in G_P.
     for (int j=0; j<m; ++j) {
        int Cj_node_idx = n+j; // Node index for column j
         if (degree_in_path[Cj_node_idx] > 0) { // Only for columns intersecting the path
            for(int neighbor_idx : adj[Cj_node_idx]) { // Neighbors are u_i nodes (indices i)
                eq_coeffs[Cj_node_idx][neighbor_idx] = 1; // Coefficient for u_i is 1
            }
            eq_coeffs[Cj_node_idx][Cj_node_idx] = -degree_in_path[Cj_node_idx]; // Coefficient for v_j is -degree |P_j|
            eq_const[Cj_node_idx] = -C_prime[j]; // Constant term is -S_col[j]
         }
    }

    // Prepare for the substitution solver (BFS on the equation dependencies).
    // `var_to_eqs[k]` stores indices of equations that involve variable k.
    vector<vector<int>> var_to_eqs(num_vars);
    // `num_unknowns_in_eq[k]` counts how many unknown variables are currently in equation k.
    vector<int> num_unknowns_in_eq(num_vars);

    for(int eq_idx = 0; eq_idx < num_vars; ++eq_idx) {
         // Skip nodes not involved in the path (degree 0)
         if (degree_in_path[eq_idx] == 0) continue;

         int count = 0; // Count variables in this equation
         for(auto const& [var_idx, coeff] : eq_coeffs[eq_idx]) {
             var_to_eqs[var_idx].push_back(eq_idx); // Record that var_idx appears in eq_idx
             count++;
         }
         num_unknowns_in_eq[eq_idx] = count; // Store initial count of variables
    }

    // Queue for equations ready to be solved (exactly one unknown variable remaining).
    queue<int> solve_queue;

    // Initialize the process by fixing one potential. We fix u_0 = 0.
    // This is valid because potentials are determined up to an additive constant.
    // The path starts at (0,0), so row 0 (node 0) must be involved in the system.
    if (degree_in_path[0] > 0 && !potential_known[0]) {
        potentials[0] = 0;
        potential_known[0] = true;

        // Propagate the knowledge u_0 = 0.
        for(int eq_idx : var_to_eqs[0]) { // For each equation involving u_0
            if (eq_coeffs[eq_idx].count(0)) { // If u_0 (variable index 0) is still in the equation map
                 // The constant term doesn't change since we substitute 0:
                 // eq_const[eq_idx] -= eq_coeffs[eq_idx][0] * potentials[0];
                 eq_coeffs[eq_idx].erase(0); // Remove u_0 from the equation's terms
                 num_unknowns_in_eq[eq_idx]--; // Decrement count of unknowns
                // If only one unknown remains, add the equation to the queue
                if (num_unknowns_in_eq[eq_idx] == 1) {
                    solve_queue.push(eq_idx);
                }
            }
        }
    }
    // If somehow degree_in_path[0] was 0, we'd need a different starting point, but this shouldn't happen.

    // BFS-like substitution process: Solve equations with one unknown and propagate results.
    while(!solve_queue.empty()) {
        int eq_idx = solve_queue.front();
        solve_queue.pop();

        // If equation state changed (e.g., processed already, or became inconsistent)
        if (num_unknowns_in_eq[eq_idx] != 1) continue;
        // If the equation has no terms left (can happen for check equations like 0=0)
        if (eq_coeffs[eq_idx].empty()) continue;

        // Find the single remaining unknown variable and its coefficient.
        // The map eq_coeffs[eq_idx] should contain exactly one entry.
        auto const& [unknown_var, unknown_var_coeff] = *eq_coeffs[eq_idx].begin();

        // Coefficient should not be zero in this problem structure.
        if (unknown_var_coeff == 0) continue;
        // Variable should not be already known if logic is correct.
        if (potential_known[unknown_var]) continue;

        // Solve for the unknown variable: coeff * var = const => var = const / coeff
        // Division should be exact since problem guarantees integer solution.
        potentials[unknown_var] = eq_const[eq_idx] / unknown_var_coeff;
        potential_known[unknown_var] = true; // Mark variable as known

        // Propagate the value of `potentials[unknown_var]` to other equations.
        for(int next_eq_idx : var_to_eqs[unknown_var]) {
            // Check if the solved variable `unknown_var` is present in `next_eq_idx`.
            if (eq_coeffs[next_eq_idx].count(unknown_var)) {
                 // Update constant term: const -= coeff * value
                 eq_const[next_eq_idx] -= eq_coeffs[next_eq_idx][unknown_var] * potentials[unknown_var];
                 // Remove the solved variable from the equation map.
                 eq_coeffs[next_eq_idx].erase(unknown_var);
                 // Decrement the count of unknowns for this equation.
                 num_unknowns_in_eq[next_eq_idx]--;
                 // If this equation now has only one unknown, add it to the queue.
                if (num_unknowns_in_eq[next_eq_idx] == 1) {
                    solve_queue.push(next_eq_idx);
                }
            }
        }
    }

    // Construct the final grid `b`.
    vector<vector<ll>> b = a; // Start with initial grid `a`.
    // Overwrite values for cells on the path using the calculated potentials.
    for(const auto& p : path_cells) {
        int r_idx = p.first;  // row index
        int c_idx = p.second; // column index
        ll u_i = potentials[r_idx];       // Potential for row i (node index i)
        ll v_j = potentials[n + c_idx]; // Potential for col j (node index n+j)
        // Set final value b_ij = u_i - v_j for path cell (i,j).
        b[r_idx][c_idx] = u_i - v_j;
    }

    // Output the resulting grid `b`.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << b[i][j] << (j == m - 1 ? "" : " "); // Print elements separated by spaces
        }
        cout << "\n"; // Newline after each row
    }
}

int main() {
    // Faster I/O operations for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        solve(); // Solve each test case
    }
    return 0;
}