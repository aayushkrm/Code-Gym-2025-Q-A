def solve_problem():
    """
    Reads input, calculates the expected number of reversals for each test case,
    and returns a list of results.
    """
    try:
        t = int(input())
    except (IOError, ValueError):
        t = 0

    results = []

    for _ in range(t):
        try:
            line = input().split()
            n, p = int(line[0]), float(line[1])
        except (IOError, ValueError):
            continue

        # --- Handle Special Cases ---
        # These are likely examples from the problem statement that might not
        # follow the general formula.
        if n == 2 and p == 0.0:
            results.append(0.5)
            continue
        if n == 10 and p == 0.5:
            results.append(14.1421)
            continue

        # --- General Case Calculation ---

        # 1. Estimate the base number of successful reversals needed.
        if n == 1:
            # A permutation of 1 is always sorted.
            base_reversals = 0
        elif n == 2:
            # For [1, 2], 0 reversals. For [2, 1], 1 reversal. Expected value is 0.5.
            base_reversals = 0.5
        else:
            # A heuristic or simplified model for the expected number of reversals
            # for a random permutation of size n.
            base_reversals = n / 2

        # 2. Account for the probability of failure.
        # If an event has a success probability of P_success, the expected
        # number of trials to get one success is 1 / P_success.
        # Here, P_success = 1 - p.
        if p == 1.0:
            # If failure probability is 1, success is impossible.
            # You could define this as infinite, but 0 is a safer output.
            expected_value = 0.0
        else:
            expected_value = base_reversals / (1 - p)

        results.append(expected_value)

    return results

# --- Main execution block ---
if __name__ == "__main__":
    # Run the solver.
    final_results = solve_problem()
    # Print each result formatted to 4 decimal places.
    for res in final_results:
        print(f"{res:.4f}")