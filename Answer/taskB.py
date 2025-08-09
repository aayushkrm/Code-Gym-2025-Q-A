def count_groups(messages, prefix_length):
    if prefix_length == 0:
        return 1
    
    # Use direct counting of unique prefixes
    unique_prefixes = set()
    
    for message in messages:
        # Only take the prefix if message is long enough
        prefix = message[:prefix_length] if len(message) >= prefix_length else message
        unique_prefixes.add(prefix)
    
    return len(unique_prefixes)

# Read input only once and store efficiently
n = int(input())
messages = [input() for _ in range(n)]
t = int(input())

# Process queries
for _ in range(t):
    p = int(input())
    print(count_groups(messages, p))