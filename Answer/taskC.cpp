#include <cstdio>      // For fread, fwrite, EOF
#include <algorithm>   // For std::sort, std::upper_bound
#include <new>         // For std::nothrow during allocation

// Use long long for bicep sizes and parameters to avoid potential overflow.
// Values can reach 10^9, and 2 * value can reach 2 * 10^9, which fits in long long.
using ll = long long;

// --- Custom Fast Input/Output ---
// Using buffered I/O (fread/fwrite) to minimize I/O overhead, which can
// be critical when real-time limits are tight or significantly different
// from CPU time limits.
namespace FastIO {
    // Input buffer settings
    const int BUFFER_SIZE_IN = 1 << 20; // 1MB input buffer
    char input_buffer[BUFFER_SIZE_IN];
    int input_ptr = 0; // Current position in the input buffer
    int bytes_read = 0; // Number of bytes read into the buffer in the last fread call

    // Reads a single character, refilling the buffer if necessary.
    inline char get_char() {
        // If buffer is exhausted, read more data from stdin
        if (input_ptr == bytes_read) {
            bytes_read = fread(input_buffer, 1, BUFFER_SIZE_IN, stdin);
            input_ptr = 0; // Reset buffer pointer
            // If fread read 0 bytes, we've reached the end of the file
            if (bytes_read == 0) return EOF;
        }
        // Return the next character from the buffer
        return input_buffer[input_ptr++];
    }

    // Reads a long long integer from the buffered input.
    // Assumes non-negative integers as per problem constraints.
    inline ll read_ll() {
        ll x = 0;       // Stores the resulting number
        char c = get_char(); // Get the first character

        // Skip any leading non-digit characters (e.g., whitespace)
        while (c < '0' || c > '9') {
            c = get_char();
             // Basic check for EOF while skipping characters
             if (c == EOF) return 0; // Or handle error as appropriate
        }

        // Process digit characters to build the number
        while (c >= '0' && c <= '9') {
            // Efficient multiplication by 10: x = x * 10 + (c - '0')
            // using bit shifts: (x << 3) + (x << 1) == x * 8 + x * 2 == x * 10
            x = (x << 3) + (x << 1) + (c - '0');
            c = get_char(); // Get the next character
        }
        return x; // Return the parsed number
    }

    // Reads an integer (convenience function using read_ll).
    inline int read_int() {
         return (int) read_ll();
    }


    // Output buffer settings
    const int BUFFER_SIZE_OUT = 1 << 20; // 1MB output buffer
    char output_buffer[BUFFER_SIZE_OUT];
    int output_ptr = 0; // Current position in the output buffer

    // Writes a single character to the output buffer, flushing if full.
    inline void put_char(char c) {
        // If the buffer is full, write its contents to stdout
        if (output_ptr == BUFFER_SIZE_OUT) {
            fwrite(output_buffer, 1, BUFFER_SIZE_OUT, stdout);
            output_ptr = 0; // Reset buffer pointer
        }
        // Add the character to the buffer
        output_buffer[output_ptr++] = c;
    }

    // Writes a long long integer to the output buffer.
    // Handles non-negative numbers efficiently.
    inline void write_ll(ll n) {
        // Handle the special case of 0
        if (n == 0) {
            put_char('0');
            put_char('\n'); // Add newline after each number as required
            return;
        }
        // Temporary buffer to store digits in reverse order
        char temp_buffer[25]; // Sufficient space for max long long digits + newline + null
        int digit_count = 0;
        // Extract digits by repeatedly taking modulo 10
        while (n > 0) {
             temp_buffer[digit_count++] = (n % 10) + '0'; // Convert digit to char
             n /= 10; // Move to the next digit
        }
        // Write digits from the temporary buffer in the correct order
        for (int i = digit_count - 1; i >= 0; --i) {
            put_char(temp_buffer[i]);
        }
        // Add the required newline character
        put_char('\n');
    }

    // Flushes any remaining data in the output buffer to stdout.
    // Must be called at the end of the program.
    inline void flush_output() {
        // If there's anything in the buffer, write it out
        if (output_ptr > 0) {
            fwrite(output_buffer, 1, output_ptr, stdout);
            output_ptr = 0; // Reset pointer (optional, program ends anyway)
        }
    }

} // namespace FastIO


int main() {
    // Use custom fast I/O functions for reading input
    int n = FastIO::read_int(); // Number of opponents
    int q = FastIO::read_int(); // Number of stages (queries)

    // Dynamically allocate memory using a C-style array for opponent sizes.
    // std::nothrow ensures nullptr is returned on failure instead of an exception.
    ll* a = new (std::nothrow) ll[n];
    // Basic check for allocation failure, crucial for large N or tight memory limits.
    if (!a) {
        return 1; // Indicate an error if memory allocation failed
    }

    ll A_max = 0; // Variable to track the maximum opponent bicep size

    // Read opponent sizes and find the maximum among them.
    // Time complexity: O(N)
    for (int i = 0; i < n; ++i) {
        a[i] = FastIO::read_ll(); // Read size using fast input
        if (a[i] > A_max) {
            A_max = a[i]; // Update maximum if current size is larger
        }
    }

    // Calculate the minimum size Artyom needs just to win.
    // Must be strictly greater than the largest opponent size.
    ll B_min_win = A_max + 1;

    // Sort the array of opponent sizes. This allows using binary search later.
    // Time complexity: O(N log N)
    std::sort(a, a + n);

    // Process each of the q queries.
    // Time complexity: O(Q log N) for this loop.
    for (int j = 0; j < q; ++j) {
        ll k_j = FastIO::read_ll(); // Read the secret parameter for this stage

        // Determine the minimum valid bicep size B for Artyom.
        // Conditions: B >= B_min_win AND B <= 2 * m
        // where m = min({p | p > k_j} among all participants)

        // Case 1: If k_j is already greater than or equal to the maximum opponent size.
        if (k_j >= A_max) {
             // To win, Artyom needs B >= B_min_win = A_max + 1.
             // Test B = B_min_win:
             //   Win: B_min_win >= B_min_win (True)
             //   Disqualification: B_min_win > A_max >= k_j, so Artyom's size is > k_j.
             //                     No opponent size a_i is > k_j.
             //                     Thus, m = B_min_win (Artyom is the only one > k_j).
             //                     Check: B_min_win <= 2 * m => B_min_win <= 2 * B_min_win (True).
             // B_min_win works and is the minimum.
             FastIO::write_ll(B_min_win); // Output result using fast output
        } else {
            // Case 2: k_j < A_max.
            // This guarantees that at least one opponent size a_i is > k_j.
            // Find m_prime = min({a_i | a_i > k_j}) using binary search.
            // std::upper_bound finds the first element strictly greater than k_j.
            // Time complexity: O(log N)
            ll* it = std::upper_bound(a, a + n, k_j);
            // 'it' points to the first element > k_j. Guaranteed valid pointer since k_j < A_max.
            ll m_prime = *it; // Dereference to get the minimum opponent size > k_j.

            // Now, test if Artyom can win with B = B_min_win without disqualification.
            // Non-disqualification check: B_min_win <= 2 * m
            // where m = min(m_prime, B_min_win).
            // This simplifies to checking: B_min_win <= 2 * m_prime
            // Need to be careful about potential overflow if intermediate results were huge,
            // but 2 * m_prime fits within long long (2 * 10^9 < 9 * 10^18).
            if (B_min_win <= 2 * m_prime) {
                // B_min_win satisfies winning and non-disqualification. It's the minimum.
                 FastIO::write_ll(B_min_win);
            } else {
                // B_min_win > 2 * m_prime. Choosing B = B_min_win leads to disqualification
                // because m would be m_prime, and B_min_win > 2m.
                // As derived previously, no B > B_min_win can work either. Impossible.
                 FastIO::write_ll(0);
            }
        }
    }

    // Ensure all buffered output is written to stdout before the program exits.
    FastIO::flush_output();

    // Deallocate the memory allocated with 'new'.
    delete[] a;

    return 0; // Indicate successful execution.
}