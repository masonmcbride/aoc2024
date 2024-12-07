with open('input.txt','r') as f:
    G = {(i,j):c for i,r in enumerate(f.readlines()) for j,c in enumerate(r)}
    g = G.keys()

D = -1,0,1
T = [list('XMAS')]

part1 = sum([G.get((i+di*n,j+dj*n)) for n in range(4)] in T 
            for di in D for dj in D for i,j in g)

T = [list('MAS'),list('SAM')]

part2 = sum([G.get((i+d,j+d)) for d in D] in T
            and [G.get((i+d,j-d)) for d in D] in T
            for i,j in g)
            
print(f"{part1=}")
print(f"{part2=}")