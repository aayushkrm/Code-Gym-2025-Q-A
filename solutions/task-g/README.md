# Task G: Maximizing "Kachistost"

## Problem Description

*This problem description is inferred from the solution code.*

You are given the scores of four people: Petya, Vlad, Vadim, and Vasya. You need to determine a score for a fifth person, Artem, to maximize the "kachistost".

The "kachistost" is defined as the number of the following equations that hold true after you choose a positive integer score for Artem:

1.  `Petya + Vlad = Artem`
2.  `Vlad + Artem = Vadim`
3.  `Artem + Vadim = Vasya`

The goal is to find the maximum number of these equations that can be satisfied simultaneously by a single valid choice for Artem's score.

## Solution Approach

The solution is based on the realization that there are only a few "interesting" values for Artem's score to check. Instead of checking all possible numbers, we only need to check the values that would satisfy at least one of the equations.

1.  **Identify Candidate Values for Artem:** The code first determines the potential values for Artem's score. If a value for Artem is going to satisfy any of the equations, it must be one of these:
    *   To satisfy equation 1: `Artem = Petya + Vlad`
    *   To satisfy equation 2: `Artem = Vadim - Vlad`
    *   To satisfy equation 3: `Artem = Vasya - Vadim`

2.  **Store Unique Candidates:** These three potential values are the only candidates worth checking. Any other value for Artem would not satisfy any of the equations, resulting in a kachistost of 0. The code calculates these three values and stores them in a `set` to handle any duplicates. It also ensures that candidate values are positive, as required.

3.  **Test Each Candidate:** The solution then iterates through the unique, positive candidate values for Artem. For each candidate:
    *   It initializes a `kachistost` counter to 0.
    *   It checks how many of the three equations are satisfied with this candidate value.
    *   The `kachistost` counter is incremented for each satisfied equation.

4.  **Find the Maximum:** The maximum `kachistost` found across all candidate values is tracked and returned as the final answer.

This approach is very efficient because it narrows down the infinite number of possible choices for Artem's score to a small, finite set of at most three candidates.
