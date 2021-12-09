#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int dp[5001][5001];

int main() {
  int n, q;

  for (int i = 0; i < 5001; i++) {
    dp[i][1] = 1;
    dp[1][i] = 1;
  }

  ll ans1, ans2;
  for (int i = 2; i < 5001; i++) {
    for (int j = 2; j < 5001; j++) {
      ans1 = (i - j) * (ll)dp[i - 1][j - 1];
      ans2 = j * (ll)dp[i - 1][j];
      dp[i][j] = (ans1 + ans2) % (int)(1e9 + 7);
    }
  }

  while (scanf("%d %d", &n, &q) == 2) {
    int k;

    for (int i = 0; i < q; i++) {
      if (i > 0) putchar_unlocked(' ');
      scanf("%d", &k);
      printf("%d", dp[n][min(n, k)]);
    }
    putchar_unlocked('\n');
  }
}
