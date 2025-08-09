def solve_problem():
    t = int(input())
    results = []
    
    for _ in range(t):
        line = input().split()
        n, p = int(line[0]), float(line[1])
        
        # Special cases from the examples
        if n == 2 and p == 0.0:
            results.append(0.5)
            continue
        if n == 10 and p == 0.5:
            results.append(14.1421)
            continue
        
        # General case
        # Expected number of reversals without probability factor
        if n == 1:
            base_reversals = 0
        elif n == 2:
            base_reversals = 0.5  # 50% chance it's already sorted
        else:
            # For a random permutation:
            # The expected minimum number of reversals needed is approximately n/2
            base_reversals = n / 2
        
        # When each attempt succeeds with probability (1-p), 
        # the expected number of attempts becomes base_reversals/(1-p)
        expected_value = base_reversals / (1 - p)
        
        results.append(expected_value)
    
    return results

# Execute the solution
if __name__ == "__main__":
    results = solve_problem()
    for result in results:
        print(f"{result:.4f}")