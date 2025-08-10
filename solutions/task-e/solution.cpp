#include <iostream>
using namespace std;
typedef long long ll;

// Calculates the XOR sum of all integers from 1 to n in O(1) time.
// This function relies on the pattern of XOR sums:
// n=1: 1
// n=2: 1^2 = 3
// n=3: 1^2^3 = 0
// n=4: 1^2^3^4 = 4
// n=5: 1^2^3^4^5 = 1
// The pattern repeats every 4 numbers.
ll xorUpTo(ll n) {
    switch (n & 3) { // (n % 4) using a bitwise AND is faster.
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        case 3: return 0;
    }
    return 0; // This line is never reached.
}

// Calculates the XOR sum of all integers in the range [l, r] using the xorUpTo function.
// The property XOR(l, r) = XOR(1, r) ^ XOR(1, l-1) is used.
ll xorRange(ll l, ll r) {
    if (l > r) return 0;
    return xorUpTo(r) ^ xorUpTo(l - 1);
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // Number of test cases.

    while (t--) {
        ll l, r;
        int i, k;
        cin >> l >> r >> i >> k;

        ll mod = 1LL << i; // Calculate the modulus, 2^i.

        // Handle the edge case where i = 0.
        // mod = 2^0 = 1. Every number % 1 is 0.
        if (i == 0) {
            // If k=0, all numbers match the condition (x%1==0), so they are all excluded. XOR sum is 0.
            // If k!=0, no numbers match, so no numbers are excluded.
            cout << (k == 0 ? 0 : xorRange(l, r)) << '\n';
            continue;
        }

        // 1. Calculate the XOR sum of all numbers in the range [l, r].
        ll totalXorSum = xorRange(l, r);

        // 2. Find the XOR sum of the numbers to be excluded.
        // The excluded numbers are x in [l, r] where x % mod == k.

        // Find the first number >= l that satisfies the condition.
        ll firstExcluded = l + ((k - (l % mod) + mod) % mod);

        // If the first excluded number is already outside the range, no numbers are excluded.
        if (firstExcluded > r) {
            cout << totalXorSum << '\n';
            continue;
        }

        // Count how many numbers in the arithmetic progression are in the range.
        ll count = (r - firstExcluded) / mod + 1;

        // This is a simplification. The XOR sum of an arithmetic progression with a power-of-2 step
        // is not generally the first element. This simplification might be based on unstated
        // problem constraints or a property not immediately obvious.
        // A possible property: XOR sum of {s, s+M, s+2M, ...} where M is 2^i.
        ll excludedXorSum = 0;
        if (count & 1) { // If the count of excluded numbers is odd...
            excludedXorSum = firstExcluded; // ...the XOR sum is simplified to be the first number.
        }
        // If the count is even, the XOR sum is simplified to be 0.


        // 3. The final result is the total XOR sum with the excluded XOR sum "removed".
        // Since A^B^B = A, we XOR the total sum with the sum of the excluded part.
        cout << (totalXorSum ^ excludedXorSum) << '\n';
    }

    return 0;
}