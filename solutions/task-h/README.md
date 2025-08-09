# Task H: Expected Reversals with Failure Probability

## Problem Description

*This problem description is inferred from the solution code.*

This problem asks for the expected number of reversal operations needed to sort a random permutation of `n` elements. The complexity is that each attempted reversal operation has a probability `p` of failing (and thus doing nothing).

## Solution Approach

The solution calculates the expected value by combining the expected number of reversals in a deterministic scenario with the probability of failure.

1.  **Base Expected Reversals:** First, the solution estimates the expected number of reversals needed to sort a random permutation of size `n` *without* considering the probability of failure.
    *   For `n=1`, the permutation is already sorted, so 0 reversals are needed.
    *   For `n=2`, there's a 50% chance the permutation is sorted (`[1, 2]`) and a 50% chance it's not (`[2, 1]`). If it's not sorted, one reversal is needed. So the expected number of reversals is `0.5 * 0 + 0.5 * 1 = 0.5`. The code uses this value directly.
    *   For `n > 2`, the code uses an approximation that the expected number of reversals is `n / 2`. This is a heuristic or a simplified model of the complex "pancake sorting" problem.

2.  **Geometric Distribution for Attempts:** The probability of failure introduces a concept from probability theory related to the Geometric distribution. If a single successful operation is required, and the probability of success is `(1-p)`, the expected number of *attempts* needed to achieve that one success is `1 / (1-p)`.

3.  **Combining the Concepts:** The solution combines these two ideas. If the base number of successful reversals needed is `E_base`, and each attempt succeeds with probability `(1-p)`, then the total expected number of *attempts* is:
    `Total Expected Attempts = E_base / (1 - p)`

4.  **Special Cases:** The code also includes hardcoded answers for two specific inputs (`n=2, p=0.0` and `n=10, p=0.5`). These might be examples from the problem statement that either serve as a baseline or perhaps follow a different logic than the general case.

The final result is printed with a fixed precision of 4 decimal places.
