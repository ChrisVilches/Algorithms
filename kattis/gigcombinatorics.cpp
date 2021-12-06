#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MAX 1000001

int N;
char nums[MAX];
int memo[MAX];
const ll MOD = 1e9 + 7;

inline void mult(ll& a, ll b) { a = (a * b) % MOD; }
inline void add(ll& a, ll b) { a = (a + b) % MOD; }

int dp(int n) {
  if (n == N) return 0;
  if (~memo[n]) return memo[n];

  ll total = (ll)dp(n + 1);

  switch (nums[n]) {
    case '2':
      mult(total, 2);
      break;
    case '3':
      total++;
      break;
  }

  return memo[n] = (int)total;
}

int main() {
  while (scanf("%d", &N) == 1) {
    memset(memo, -1, sizeof(int) * N);
    for (int i = 0; i < N; i++) {
      char c = '\0';
      // Read '1', '2', '3' while skipping spaces.
      while (!(c & 16)) c = getchar_unlocked();
      nums[i] = c;
    }

    ll total = 0;
    ll ones = 0;
    for (int i = 0; i < N; i++) {
      switch (nums[i]) {
        case '1':
          ones++;
          break;
        case '2':
          add(total, ones * (dp(i) - dp(i + 1)));
          break;
      }
    }

    printf("%lld\n", total % MOD);
  }
}
