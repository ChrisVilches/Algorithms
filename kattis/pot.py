import math

n = int(input())

total = 0

for _ in range(n):
    num = int(input())
    pot = num % 10
    num = math.floor(num/10)
    total += num ** pot

print(total)
