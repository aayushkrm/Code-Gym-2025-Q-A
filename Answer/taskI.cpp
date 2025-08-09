#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

int main() {
    // Optimize input/output
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> claims(n);
        for (int i = 0; i < n; i++) {
            cin >> claims[i];
        }
        
        // Use 2D arrays instead of 3D for better cache locality
        // prev[chems][last] = configurations for previous position
        // curr[chems][last] = configurations for current position
        vector<vector<long long>> prev(n + 1, vector<long long>(2, 0));
        vector<vector<long long>> curr(n + 1, vector<long long>(2, 0));
        
        // Base case
        prev[0][0] = 1;
        
        for (int pos = 0; pos < n; pos++) {
            // Clear current state
            for (int chems = 0; chems <= pos + 1; chems++) {
                curr[chems][0] = curr[chems][1] = 0;
            }
            
            for (int chems = 0; chems <= pos; chems++) {
                // Natural at previous position
                if (prev[chems][0] > 0) {
                    // Try placing natural (must tell truth)
                    if (claims[pos] == chems) {
                        curr[chems][0] = (curr[chems][0] + prev[chems][0]) % MOD;
                    }
                    
                    // Try placing chemical (can say anything)
                    curr[chems+1][1] = (curr[chems+1][1] + prev[chems][0]) % MOD;
                }
                
                // Chemical at previous position
                if (prev[chems][1] > 0) {
                    // Can only place natural after chemical
                    if (claims[pos] == chems) {
                        curr[chems][0] = (curr[chems][0] + prev[chems][1]) % MOD;
                    }
                }
            }
            
            // Swap arrays for next iteration
            swap(prev, curr);
        }
        
        // Sum all valid configurations
        long long result = 0;
        for (int chems = 0; chems <= n; chems++) {
            result = (result + prev[chems][0] + prev[chems][1]) % MOD;
        }
        
        cout << result << "\n";
    }
    
    return 0;
}