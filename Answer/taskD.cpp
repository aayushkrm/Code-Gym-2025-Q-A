#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Check if there's a path from start to end in the graph
bool hasPath(const vector<vector<int>>& graph, int start, int end) {
    int n = graph.size() - 1;
    vector<bool> visited(n + 1, false);
    queue<int> q;
    
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        if (curr == end) return true;
        
        for (int next : graph[curr]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<int>> graph(n + 1);
    vector<pair<int, int>> corridors;
    
    // Read the n-1 corridors
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        corridors.push_back({a, b});
    }
    
    int q;
    cin >> q;
    
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }
    
    int bestCorridorIndex = 0;
    int maxPossiblePaths = -1;
    vector<bool> bestResults;
    
    // Try making each corridor bidirectional and evaluate
    for (int i = 0; i < n - 1; i++) {
        int a = corridors[i].first;
        int b = corridors[i].second;
        
        // Add the reverse edge temporarily
        graph[b].push_back(a);
        
        // Evaluate paths for each query
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
        
        // Update best corridor if this one is better
        if (possiblePaths > maxPossiblePaths) {
            maxPossiblePaths = possiblePaths;
            bestCorridorIndex = i + 1;  // 1-indexed for output
            bestResults = results;
        }
        
        // Remove the reverse edge for the next iteration
        graph[b].pop_back();
    }
    
    // Output the result
    cout << bestCorridorIndex << endl;
    
    // Output results for each query
    for (bool result : bestResults) {
        cout << (result ? "YES" : "NO") << endl;
    }
    
    return 0;
}