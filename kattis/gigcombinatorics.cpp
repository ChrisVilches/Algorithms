#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MAX 1000010

int N, nums[MAX];
ll memo[2][MAX];
const ll MOD = 1e9 + 7;

inline ll mult(ll a, ll b) { return (a * b) % MOD; }
inline ll add(ll a, ll b) { return (a + b) % MOD; }

ll dp(bool first, int n) {
  if (n == N) return 0;
  if (~memo[first][n]) return memo[first][n];

  ll total = dp(false, n + 1);

  if (nums[n] == 2 && !first)
    total = mult(total, 2);
  else if (nums[n] == 3)
    total = add(total, 1);

  return memo[first][n] = total;
}

int main() {
  while (scanf("%d", &N) == 1) {
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < N; i++) scanf("%d", &nums[i]);

    ll total = 0;
    ll ones = 0;
    for (int i = 0; i < N; i++)
      if (nums[i] == 1)
        ones++;
      else if (nums[i] == 2)
        total = add(total, mult(ones, dp(true, i)));

    printf("%lld\n", total);
  }
}
