import re

with open('input.txt','r') as f:
    inp = 'do()' + f.read().replace('\n','') + 'don\'t()'

part1 = sum(int(x)*int(y) for x,y in re.findall(r"mul\((\d+),(\d+)\)", inp))
inp = "".join(re.findall(r'do\(\)(.*?)don\'t\(\)',inp))
part2 = sum(int(x)*int(y) for x,y in re.findall(r"mul\((\d+),(\d+)\)", inp))

print(f"{part1=}")
print(f"{part2=}")