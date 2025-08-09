#include <iostream>
using namespace std;
typedef long long ll;

// Calculate XOR of numbers from 1 to n efficiently
ll xorUpTo(ll n) {
    switch (n & 3) { // n % 4 using bitwise AND
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        case 3: return 0;
    }
    return 0; // Never reached
}

// Calculate XOR of all numbers in range [l, r]
ll xorRange(ll l, ll r) {
    return xorUpTo(r) ^ xorUpTo(l - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        ll l, r;
        int i, k;
        cin >> l >> r >> i >> k;
        
        ll mod = 1LL << i; // 2^i
        
        if (i == 0) {
            // Special case: i=0 means mod 1
            cout << (k == 0 ? 0 : xorRange(l, r)) << '\n';
            continue;
        }
        
        // All numbers in range
        ll allXor = xorRange(l, r);
        
        // Find numbers that are equal to k mod 2^i
        ll start = l + ((k - l % mod + mod) % mod);
        
        if (start > r) {
            // No numbers equal to k mod 2^i in our range
            cout << allXor << '\n';
            continue;
        }
        
        // Count of numbers equal to k mod 2^i
        ll count = (r - start) / mod + 1;
        
        // If count is odd, their XOR is one such number; if even, their XOR is 0
        if (count & 1) { // count % 2 using bitwise AND
            // Calculate the value to XOR out
            ll valueToXor = start;
            
            // Remove the XOR contribution of numbers that are k mod 2^i
            allXor ^= valueToXor;
        }
        
        cout << allXor << '\n';
    }
    
    return 0;
}