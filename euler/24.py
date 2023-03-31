from itertools import permutations

perms = sorted(list(permutations('0123456789', 10)))
print(''.join(perms[1000000-1]))

    
