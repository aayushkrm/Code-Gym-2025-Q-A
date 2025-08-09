# Task I: Natural vs. Chemical Configurations

## Problem Description

*This problem description is inferred from the solution code.*

This is a counting problem that can be solved with dynamic programming. You have `n` athletes in a line, and each can be either "natural" or "chemical". They each make an integer claim. The validity of a configuration is determined by three rules:

1.  **Truthful Naturals:** A natural athlete at position `i` must make a claim `claims[i]` that is exactly equal to the number of chemical athletes before them (in positions `0` to `i-1`).
2.  **Lying Chemicals:** A chemical athlete can make any claim; their `claims[i]` value doesn't matter.
3.  **Placement Rule:** A chemical athlete cannot be followed by another chemical athlete.

The goal is to find the total number of valid sequences of natural and chemical assignments for the `n` athletes, with the result taken modulo 998244353.

## Solution Approach

The solution uses dynamic programming to build up the number of valid configurations position by position.

### DP State

The state of our DP can be defined as `dp[pos][chems][last]`, representing the number of valid configurations for the first `pos` positions, where:
*   `pos`: The current position being considered (from 0 to `n-1`).
*   `chems`: The total number of chemical athletes placed so far.
*   `last`: The type of athlete at the previous position (`0` for natural, `1` for chemical).

The solution uses a space-optimized DP approach with two 2D arrays, `prev` and `curr`, to represent the DP states for the previous and current positions, reducing the space complexity from O(n^2) to O(n).
`prev[chems][last]` stores the count for the previous position `pos-1`.

### DP Transitions

The code iterates from `pos = 0` to `n-1`. For each position, it calculates the `curr` DP table based on the `prev` table.

Let's consider the state `prev[chems][last]` at position `pos-1`. We are now deciding what to place at `pos`.

1.  **If the previous athlete (`pos-1`) was Natural (`last == 0`):**
    *   **Place Natural at `pos`:** This is a valid move. The new state will have `chems` chemical athletes. The claim `claims[pos]` must be true, so this transition is only possible if `claims[pos] == chems`.
        `curr[chems][0] += prev[chems][0]`
    *   **Place Chemical at `pos`:** This is also a valid move. The new state will have `chems + 1` chemical athletes. A chemical can say anything, so we don't need to check the claim.
        `curr[chems+1][1] += prev[chems][0]`

2.  **If the previous athlete (`pos-1`) was Chemical (`last == 1`):**
    *   **Place Natural at `pos`:** This is the only valid move due to the placement rule. The new state has `chems` chemical athletes. The claim must be true: `claims[pos] == chems`.
        `curr[chems][0] += prev[chems][1]`
    *   **Place Chemical at `pos`:** This is forbidden by the rules.

### Base Case

Before the loop starts (`pos = -1`), we can imagine a single state: 0 athletes placed, 0 chemicals, and the "previous" athlete was natural (or some other non-chemical state). This is represented by: `prev[0][0] = 1`.

### Final Result

After iterating through all `n` positions, the `prev` table holds the results for the full configurations. The final answer is the sum of all possible valid states: the sum of `prev[chems][0]` and `prev[chems][1]` over all possible values of `chems`.

This DP approach correctly counts all valid configurations by building them incrementally, ensuring all rules are satisfied at each step. The modulo operation is applied at each addition to prevent overflow.
