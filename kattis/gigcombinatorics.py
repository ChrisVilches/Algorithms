MOD = int(1e9 + 7)
nums = []
memo = []
N = None


def dp(n):
    if n == N:
        return 0
    if memo[n] != -1:
        return memo[n]

    total = dp(n + 1)

    if nums[n] == 2:
        total *= 2
    elif nums[n] == 3:
        total += 1

    memo[n] = total % MOD

    return memo[n]


while(True):
    try:
        line = input()
    except EOFError:
        break

    N = int(line)

    nums = list(map(int, input().split()))

    memo = [-1] * N

    total = 0
    ones = 0

    for i in reversed(range(N)):
        dp(i)

    for i in range(N):
        if nums[i] == 1:
            ones += 1
        elif nums[i] == 2:
            total += ones * dp(i + 1)
            total %= MOD

    print(total % MOD)
