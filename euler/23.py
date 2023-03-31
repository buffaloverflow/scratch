from factor import *

abunds = [x for x in range(1,28124) if abundant(x)]

sums = set()
for i in abunds:
    for j in abunds:
        sums.add(i+j)

print(sum(set(range(1,28124)) - sums))
        
