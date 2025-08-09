def solve(petya, vlad, vadim, vasya):
    max_kachistost = 0
    
    # We need to check all possible values for Artem
    # For each possible value, compute the kachistost
    
    # To maximize kachistost, we'll try specific values that could satisfy each condition
    possible_artem_values = set()
    
    # Case 1: a[228] + a[229] = a[230] => petya + vlad = artem
    possible_artem_values.add(petya + vlad)
    
    # Case 2: a[229] + a[230] = a[231] => vlad + artem = vadim => artem = vadim - vlad
    if vadim - vlad > 0:
        possible_artem_values.add(vadim - vlad)
    
    # Case 3: a[230] + a[231] = a[232] => artem + vadim = vasya => artem = vasya - vadim
    if vasya - vadim > 0:
        possible_artem_values.add(vasya - vadim)
    
    # Also try values that allow two equations to be satisfied simultaneously
    # For example, if we want conditions 1 and 2 to be satisfied:
    # petya + vlad = artem and vlad + artem = vadim
    # This would mean artem = petya + vlad and artem = vadim - vlad
    # So petya + vlad = vadim - vlad => 2*vlad + petya = vadim
    
    # For conditions 2 and 3:
    # vlad + artem = vadim and artem + vadim = vasya
    # This means artem = vadim - vlad and artem = vasya - vadim
    # So vadim - vlad = vasya - vadim => 2*vadim = vasya + vlad
    
    # For conditions 1 and 3:
    # petya + vlad = artem and artem + vadim = vasya
    # This means artem = petya + vlad and artem = vasya - vadim
    # So petya + vlad = vasya - vadim => petya + vlad + vadim = vasya
    
    # Check each possible value
    for artem in possible_artem_values:
        if artem <= 0:  # Skip if Artem's result is not positive
            continue
            
        kachistost = 0
        
        # Check condition 1: petya + vlad = artem
        if petya + vlad == artem:
            kachistost += 1
            
        # Check condition 2: vlad + artem = vadim
        if vlad + artem == vadim:
            kachistost += 1
            
        # Check condition 3: artem + vadim = vasya
        if artem + vadim == vasya:
            kachistost += 1
            
        max_kachistost = max(max_kachistost, kachistost)
    
    return max_kachistost

# Read input and process test cases
t = int(input())
for _ in range(t):
    a = list(map(int, input().split()))
    result = solve(a[0], a[1], a[2], a[3])
    print(result)