#include <bits/stdc++.h>
using namespace std;

int N, M;
int nums[12];
short memo[1'000'003];

short p(const int stones) {
  if (stones == 0) return 0;
  if (stones < 0) return 1;
  if (~memo[stones]) return memo[stones];

  for (int i = 0; i < M; i++)
    if (p(stones - nums[i]) == 0) return memo[stones] = 1;

  return memo[stones] = 0;
}

void solve() {
  memset(memo, -1, sizeof memo);

  for (int i = 0; i < M; i++) scanf("%d", &nums[i]);

  for (int i = 0; i < N; i++) p(i);  // Avoid stack overflow.

  printf("%s wins\n", p(N) ? "Stan" : "Ollie");
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) solve();
}
