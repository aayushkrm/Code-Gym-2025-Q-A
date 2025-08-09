def count_groups(messages, prefix_length):
    """
    Counts the number of unique prefixes of a given length in a list of messages.
    """
    if prefix_length == 0:
        return 1  # As per problem constraints, a prefix of length 0 is one group.

    # Use a set to store unique prefixes for efficient counting.
    unique_prefixes = set()

    for message in messages:
        # Extract the prefix of the given length.
        # If the message is shorter than the prefix length, the message itself is the prefix.
        prefix = message[:prefix_length]
        unique_prefixes.add(prefix)

    return len(unique_prefixes)

# Read the number of messages.
n = int(input())
# Read all messages and store them in a list.
messages = [input() for _ in range(n)]
# Read the number of queries.
t = int(input())

# Process each query.
for _ in range(t):
    # Read the prefix length for the current query.
    p = int(input())
    # Calculate and print the number of unique groups.
    print(count_groups(messages, p))