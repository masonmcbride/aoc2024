import numpy as np
from collections import Counter

#random other solution: 0.008s 3057 function calls
#my solution:           0.0001s 3050 function calls

with open('input.txt', 'r') as file:
    lines = file.readlines()
left,right = zip(*map(lambda line: map(int, line.split()), lines))
frequencies = Counter(right)
freqs = np.array([frequencies.get(li,0) for li in left])
part2 = left@freqs
left,right = np.array(sorted(left)),np.array(sorted(right))
part1 = sum(abs(left-right))

print(f"{part1=}\n{part2=}")