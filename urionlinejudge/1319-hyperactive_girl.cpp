#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M, start[107], finish[107];
const ll MOD = 1e8;
ll memo[107][107];

bool overlap(const int i, const int j) {
  return start[i] < start[j] && start[j] <= finish[i] && finish[i] < finish[j];
}

ll dp(const int prev, const int curr) {
  if (finish[curr] == M) return 1;
  if (~memo[prev][curr]) return memo[prev][curr];

  ll ans = 0;

  for (int i = 0; i < N; i++) {
    if (overlap(curr, i) && finish[prev] < start[i]) {
      ans += dp(curr, i);
    }
  }

  return memo[prev][curr] = ans % MOD;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> M >> N && N && M) {
    memset(memo, -1, sizeof memo);

    for (int i = 0; i < N; i++) {
      cin >> start[i] >> finish[i];
    }

    ll ans = 0;

    for (int i = 0; i < N; i++) {
      if (start[i] != 0) continue;

      if (finish[i] == M) ans++;

      for (int j = 0; j < N; j++) {
        if (overlap(i, j)) {
          ans += dp(i, j);
        }
      }

      ans %= MOD;
    }

    cout << ans << endl;
  }
}
