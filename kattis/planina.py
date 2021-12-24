n = int(input())

x = 3

for _ in range(n - 1):
    x += x - 1

print(x ** 2)
