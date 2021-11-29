#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll MOD = 1e8 + 7;

int A[1001];
bool B[2001];

int memo[1001][1 << 11];

int dp(int n, int accum) {
  if (n == -1) return !B[accum];
  if (memo[n][accum] != -1) return memo[n][accum];

  ll ret = 0;

  ret = (ret + (ll)dp(n - 1, accum ^ A[n])) % MOD;
  ret = (ret + (ll)dp(n - 1, accum)) % MOD;

  return memo[n][accum] = (int)ret;
}

void solve() {
  int N, M;

  memset(B, 0, sizeof B);
  memset(memo, -1, sizeof memo);
  scanf("%d %d", &N, &M);

  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }

  for (int i = 0; i < M; i++) {
    int b;
    scanf("%d", &b);
    B[b] = true;
  }

  printf("%d\n", dp(N - 1, 0));
}

int main() {
  int T;
  scanf("%d", &T);

  for (int i = 0; i < T; i++) {
    printf("Case %d: ", i + 1);
    solve();
  }
}
