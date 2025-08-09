# Task B: Grouping by Prefix

## Problem Description

*This problem description is inferred from the solution code.*

The problem is to count the number of unique groups of messages based on their prefixes of a given length. You are given a list of messages and a series of queries, each with a prefix length `p`. For each query, you need to determine how many unique prefixes of length `p` exist among the messages.

## Solution Approach

The solution first reads the number of messages `n` and the messages themselves. Then, it reads the number of queries `t`. For each query, it reads a prefix length `p` and calls the `count_groups` function.

The `count_groups` function takes the list of messages and the prefix length `p` as input. It iterates through each message and extracts its prefix of length `p`. These prefixes are stored in a set to automatically handle uniqueness. The function then returns the size of the set, which represents the number of unique prefixes.

This approach is efficient because using a set to store prefixes avoids duplicates and provides a quick way to count the unique groups.
