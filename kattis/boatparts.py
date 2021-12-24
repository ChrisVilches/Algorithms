p, n = map(int, input().split())

words = set()

found = False

for i in range(n):
    words.add(input())

    if len(words) == p:
        found = True
        print(i + 1)
        break

if not found:
    print("paradox avoided")
