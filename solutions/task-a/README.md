# Task A: Weight Distribution

## Problem Description

*This problem description is inferred from the solution code.*

The problem is to determine if a given weight `w` can be evenly distributed into two halves. The weight can only be distributed if it is a non-negative number and is divisible by 5.

If the weight can be distributed, the output should be the weight of each half, formatted to two decimal places. Otherwise, the output should be -1.

## Solution Approach

The solution reads an integer `w` from standard input. It then checks for two conditions:
1.  `w` must be non-negative (`w >= 0`).
2.  `w` must be divisible by 5 (`w % 5 == 0`).

If both conditions are true, the code calculates half of the weight and prints it with two decimal places. If either condition is false, it prints -1.

This approach is straightforward and directly implements the inferred logic of the problem.
