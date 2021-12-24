def read_tuple():
    a, b = map(int, input().split())
    return (a, b)


p1 = read_tuple()
p2 = read_tuple()
p3 = read_tuple()

min_x = min(p1[0], p2[0], p3[0])
max_x = max(p1[0], p2[0], p3[0])
min_y = min(p1[1], p2[1], p3[1])
max_y = max(p1[1], p2[1], p3[1])

q1 = (min_x, min_y)
q2 = (min_x, max_y)
q3 = (max_x, min_y)
q4 = (max_x, max_y)

points = [q1, q2, q3, q4]

for p in points:
    if p == p1 or p == p2 or p == p3:
        continue

    print(p[0], p[1])
