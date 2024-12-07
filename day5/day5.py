from collections import defaultdict, deque
with open('input.txt','r') as f:
    inp = f.read()

relations, updates = inp.split('\n\n')
R = set(tuple(rel.split('|')) for rel in relations.split('\n'))
pairs = lambda update: [(i,j) for i in range(len(update)) for j in range(i+1,len(update))]
updates = [update.split(',') for update in updates.split('\n')]
part1 = sum(map(lambda l: int(l[len(l)//2]),[u for u in updates if all((u[i],u[j]) in R for i,j in pairs(u))]))

def extract_subgraph(R, u):
    """Extract the subgraph for the elements in u from the relation R."""
    subgraph = defaultdict(set)
    in_degree = defaultdict(int)
    
    # Add only constraints that are relevant for elements in u
    for x, y in R:
        if x in u and y in u:
            subgraph[x].add(y)
            in_degree[y] += 1
    
    return subgraph, in_degree

def topological_sort(u, R):
    """Topologically sort the list of strings u according to the constraints in R."""
    subgraph, in_degree = extract_subgraph(R, u)
    
    # Kahn's algorithm for topological sorting
    queue = deque([node for node in u if in_degree[node] == 0])
    sorted_order = []

    while queue:
        node = queue.popleft()
        sorted_order.append(node)
        
        for neighbor in subgraph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)
    
    return sorted_order

part2 = sum(map(lambda l: int(l[len(l)//2]),[topological_sort(u,R) for u in updates if any((u[i],u[j]) not in R for i,j in pairs(u))]))

print(f"{part1=}")
print(f"{part2=}")