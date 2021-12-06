#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MAX 1000001

int N;
char nums[MAX];
ll memo[2][MAX];
const ll MOD = 1e9 + 7;

inline void mult(ll& a, ll b) { a = (a * b) % MOD; }
inline void add(ll& a, ll b) { a = (a + b) % MOD; }

ll dp(bool first, int n) {
  if (n == N) return 0;
  if (~memo[first][n]) return memo[first][n];

  ll total = dp(false, n + 1);

  if (nums[n] == '2' && !first)
    mult(total, 2);
  else if (nums[n] == '3')
    add(total, 1);

  return memo[first][n] = total;
}

int main() {
  while (scanf("%d", &N) == 1) {
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < N; i++) {
      char c = '\0';
      // Read '1', '2', '3' while skipping spaces.
      while (!(c & 16)) c = getchar_unlocked();
      nums[i] = c;
    }

    ll total = 0;
    ll ones = 0;
    for (int i = 0; i < N; i++)
      if (nums[i] == '1')
        ones++;
      else if (nums[i] == '2')
        add(total, ones * dp(true, i));

    printf("%lld\n", total);
  }
}
