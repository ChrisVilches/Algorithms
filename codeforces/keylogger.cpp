#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int K, N;
ll L;
ll MOD = 1e9 + 7;
ll T[800][800], zero = 0, dp[10007][800], deltas[10007];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> K >> L) {
    for (int i = 0; i < K; i++)
      for (int j = 0; j < K; j++) cin >> T[i][j];

    cin >> N;

    for (int i = 0; i < N - 1; i++) cin >> deltas[i];

    for (int k = 0; k < K; k++) {
      dp[N - 1][k + 1] = 1 + dp[N - 1][k];
    }

    for (int p = N - 2; p >= 0; p--) {
      for (int k = 0; k < K; k++) {
        dp[p][k + 1] = dp[p][k];

        int from = lower_bound(T[k], T[k] + K, deltas[p] - L) - T[k];
        int to = upper_bound(T[k], T[k] + K, deltas[p] + L) - T[k];

        dp[p][k + 1] += (dp[p + 1][to] - dp[p + 1][from] + MOD) % MOD;
      }
    }

    cout << dp[0][K] << endl;
  }
}
