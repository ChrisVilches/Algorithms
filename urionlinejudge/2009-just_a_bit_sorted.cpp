#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int dp[5001][5001];

int main() {
  int N, Q;

  for (int i = 0; i < 5001; i++) dp[i][1] = dp[1][i] = 1;

  ll A, B;
  for (int i = 2; i < 5001; i++)
    for (int j = 2; j < 5001; j++) {
      A = (i - j) * (ll)dp[i - 1][j - 1];
      B = j * (ll)dp[i - 1][j];
      dp[i][j] = (A + B) % (int)(1e9 + 7);
    }

  while (scanf("%d %d", &N, &Q) == 2) {
    int K;

    for (int i = 0; i < Q; i++) {
      if (i > 0) putchar_unlocked(' ');
      scanf("%d", &K);
      printf("%d", dp[N][min(N, K)]);
    }
    putchar_unlocked('\n');
  }
}
