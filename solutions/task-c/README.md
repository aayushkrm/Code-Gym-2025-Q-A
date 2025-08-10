# Task C: Bicep Size Competition

## Problem Description

*This problem description is inferred from the solution code.*

Artyom is participating in a bicep size competition with `n` opponents. The competition has `q` stages, each with a secret parameter `k_j`. Artyom needs to choose a bicep size `B` for each stage that satisfies two conditions:

1.  **Winning Condition:** Artyom's bicep size `B` must be strictly greater than all of his opponents' bicep sizes.
2.  **Non-Disqualification Condition:** Let `S` be the set of all participants' bicep sizes (including Artyom's) that are strictly greater than the stage parameter `k_j`. Let `m` be the minimum value in `S`. Artyom is not disqualified if `B <= 2 * m`.

For each stage, the goal is to find the minimum possible integer `B` that meets both conditions. If no such `B` exists, the answer is 0.

## Solution Approach

The solution is highly optimized for performance, using custom fast I/O and efficient algorithms.

1.  **Fast I/O:** The code uses a custom `FastIO` namespace with buffered input and output to handle large amounts of data quickly. This is a common technique in competitive programming to avoid "Time Limit Exceeded" errors.

2.  **Preprocessing:**
    *   The solution reads all `n` opponent bicep sizes and finds the maximum size, `A_max`.
    *   The minimum winning bicep size for Artyom, `B_min_win`, is determined as `A_max + 1`. This is the smallest possible value for `B` that satisfies the winning condition.
    *   The array of opponent sizes is sorted. This is a crucial step that enables the use of binary search for the queries, reducing the time complexity.

3.  **Query Processing:** For each of the `q` queries with parameter `k_j`:
    *   **Case 1: `k_j >= A_max`**: If the secret parameter is greater than or equal to the largest opponent's size, then no opponent's size is greater than `k_j`. The only participant size greater than `k_j` will be Artyom's (`B_min_win`). Thus, `m = B_min_win`. The non-disqualification condition `B_min_win <= 2 * B_min_win` is always true. So, `B_min_win` is the answer.
    *   **Case 2: `k_j < A_max`**: At least one opponent has a bicep size greater than `k_j`. The solution uses `std::upper_bound` (a binary search algorithm) on the sorted opponent sizes to find `m_prime`, the smallest opponent bicep size strictly greater than `k_j`.
        *   The solution then checks if `B_min_win` is a valid choice. The non-disqualification condition becomes `B_min_win <= 2 * m_prime`.
        *   If this condition holds, `B_min_win` is the minimum valid size.
        *   If it does not hold (`B_min_win > 2 * m_prime`), it means that choosing `B_min_win` would lead to disqualification. It can be shown that any `B > B_min_win` would also lead to disqualification, so no solution exists, and the answer is 0.

4.  **Memory Management:** The solution uses `new (std::nothrow)` for dynamic memory allocation and `delete[]` to free the memory, which is good practice in C++.

This approach is very efficient, with a time complexity of O(N log N + Q log N), making it suitable for large inputs.
