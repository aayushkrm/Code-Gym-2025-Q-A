#include <iostream>
#include <vector>
using namespace std;

// The modulo for the final result.
const int MOD = 998244353;

int main() {
    // Optimize input/output operations for speed.
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t; // Number of test cases.

    while (t--) {
        int n;
        cin >> n; // Number of athletes.

        vector<int> claims(n);
        for (int i = 0; i < n; i++) {
            cin >> claims[i];
        }

        // Dynamic Programming approach.
        // We use two 2D arrays to save space (O(N) space instead of O(N^2)).
        // `prev` holds the DP states for the previous position (pos-1).
        // `curr` is used to compute the DP states for the current position (pos).
        //
        // DP State: dp[chems][last_is_chem]
        // - chems: The number of chemical athletes placed so far.
        // - last_is_chem: A boolean (0 or 1) indicating if the athlete at the previous position was chemical.
        vector<vector<long long>> prev(n + 1, vector<long long>(2, 0));
        vector<vector<long long>> curr(n + 1, vector<long long>(2, 0));

        // Base Case: Before placing any athletes (pos = -1), there is one valid configuration:
        // an empty line with 0 chemical athletes, and we can consider the "previous" athlete as natural.
        prev[0][0] = 1;

        // Iterate through each position from 0 to n-1.
        for (int pos = 0; pos < n; pos++) {
            // Reset the 'curr' DP table for the current position.
            for (int chems = 0; chems <= pos + 1; chems++) {
                curr[chems][0] = curr[chems][1] = 0;
            }

            // Iterate through all possible states from the previous position.
            for (int chems = 0; chems <= pos; chems++) {
                // --- Transition from a state where the previous athlete was NATURAL ---
                if (prev[chems][0] > 0) {
                    // Option 1: Place a NATURAL athlete at the current position.
                    // The claim must be true: claims[pos] must equal the number of chemicals so far.
                    if (claims[pos] == chems) {
                        curr[chems][0] = (curr[chems][0] + prev[chems][0]) % MOD;
                    }

                    // Option 2: Place a CHEMICAL athlete at the current position.
                    // A chemical can say anything, so the claim is always valid.
                    // The number of chemicals increases by 1.
                    curr[chems + 1][1] = (curr[chems + 1][1] + prev[chems][0]) % MOD;
                }

                // --- Transition from a state where the previous athlete was CHEMICAL ---
                if (prev[chems][1] > 0) {
                    // Option 1: Place a NATURAL athlete at the current position.
                    // This is the only allowed move, as two chemicals cannot be adjacent.
                    // The claim must be true.
                    if (claims[pos] == chems) {
                        curr[chems][0] = (curr[chems][0] + prev[chems][1]) % MOD;
                    }
                    // Option 2 (placing a chemical) is not possible.
                }
            }

            // The `curr` table is now computed. It becomes the `prev` table for the next iteration.
            swap(prev, curr);
        }

        // After the loop, `prev` holds the DP states for the full configuration of n athletes.
        // The total number of valid configurations is the sum of all states.
        long long result = 0;
        for (int chems = 0; chems <= n; chems++) {
            result = (result + prev[chems][0] + prev[chems][1]) % MOD;
        }

        cout << result << "\n";
    }

    return 0;
}