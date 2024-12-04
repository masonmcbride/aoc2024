with open('input.txt',mode='r') as f:
    reports: list[int] = [list(map(int,line.split())) for line in f.readlines()]

part1 = 0
def is_monotonic_and_bounded(nums):
    increasing = True
    decreasing = True
    for i in range(len(nums) - 1):
        if nums[i] < nums[i + 1]:
            decreasing = False
        if nums[i] > nums[i + 1]:
            increasing = False
        if not 1 <= abs(nums[i] - nums[i + 1]) <= 3:
            return False  
        if not increasing and not decreasing:
            return False
    return True
part1 = sum(map(is_monotonic_and_bounded,reports))
part2 = 0
for report in reports:
    sublists = [report[:i] + report[i+1:] for i in range(len(report))]
    if is_monotonic_and_bounded(report) or any(is_monotonic_and_bounded(sublist) for sublist in sublists):
        part2 += 1
print(f"{part1=}")
print(f"{part2=}")
