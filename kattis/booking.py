from datetime import datetime, timedelta
import itertools


def solve(n, clean):
    events = []
    fmt = "%Y-%m-%d %H:%M"
    clean_time = timedelta(minutes=clean)

    for _ in range(n):
        line = input()
        parts = line.split()
        start = datetime.strptime(f"{parts[1]} {parts[2]}", fmt)
        end = datetime.strptime(f"{parts[3]} {parts[4]}", fmt) + clean_time
        events.append((start, 1))
        events.append((end, -1))

    events.sort()
    ans = max(itertools.accumulate(x[1] for x in events))
    print(ans)


if __name__ == "__main__":
    tests = int(input())
    for _ in range(tests):
        line = input()
        parts = line.split()
        n, clean = list(map(int, parts))
        solve(n, clean)
