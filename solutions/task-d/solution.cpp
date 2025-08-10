#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to check if a path exists from a start node to an end node using Breadth-First Search (BFS).
bool hasPath(const vector<vector<int>>& graph, int start, int end) {
    int n = graph.size() - 1;
    // Visited array to keep track of visited nodes to avoid cycles and redundant computations.
    vector<bool> visited(n + 1, false);
    // Queue for BFS traversal.
    queue<int> q;
    
    // Start BFS from the 'start' node.
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        // If the current node is the destination, a path exists.
        if (curr == end) return true;
        
        // Explore all adjacent nodes.
        for (int next : graph[curr]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    
    // If the queue becomes empty and the end node was not reached, no path exists.
    return false;
}

int main() {
    // Fast I/O for performance.
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; // Number of nodes.
    cin >> n;
    
    // Adjacency list representation of the graph.
    vector<vector<int>> graph(n + 1);
    // Store corridors to iterate through them later.
    vector<pair<int, int>> corridors;
    
    // Read the n-1 one-way corridors.
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        corridors.push_back({a, b});
    }
    
    int q; // Number of queries.
    cin >> q;
    
    // Store queries to evaluate them for each corridor modification.
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }
    
    int bestCorridorIndex = 0; // 1-based index of the best corridor to make bidirectional.
    int maxPossiblePaths = -1; // Maximum number of queries satisfied.
    vector<bool> bestResults;  // Stores the results for the best corridor choice.
    
    // Brute-force approach: try making each corridor bidirectional and evaluate the outcome.
    for (int i = 0; i < n - 1; i++) {
        int a = corridors[i].first;
        int b = corridors[i].second;
        
        // --- Simulation Step ---
        // Add the reverse edge temporarily to make the corridor bidirectional.
        graph[b].push_back(a);
        
        // Evaluate all queries with the modified graph.
        int possiblePaths = 0;
        vector<bool> results(q);
        
        for (int j = 0; j < q; j++) {
            int x = queries[j].first;
            int y = queries[j].second;
            
            results[j] = hasPath(graph, x, y);
            if (results[j]) {
                possiblePaths++;
            }
        }
        
        // Update the best corridor if the current one satisfies more queries.
        if (possiblePaths > maxPossiblePaths) {
            maxPossiblePaths = possiblePaths;
            bestCorridorIndex = i + 1;  // Store the 1-indexed corridor index.
            bestResults = results;
        }
        
        // --- Backtrack Step ---
        // Remove the temporarily added reverse edge to restore the graph for the next iteration.
        graph[b].pop_back();
    }
    
    // Output the final result.
    cout << bestCorridorIndex << endl;
    
    // Output "YES" or "NO" for each query based on the best corridor choice.
    for (bool result : bestResults) {
        cout << (result ? "YES" : "NO") << endl;
    }
    
    return 0;
}