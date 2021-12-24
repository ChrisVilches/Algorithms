x = int(input())
n = int(input())

megabytes = []

for _ in range(n):
    megabytes.append(int(input()))

total = x

for mb in megabytes:
    total += x
    total -= mb


print(total)
