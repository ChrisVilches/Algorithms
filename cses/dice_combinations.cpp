#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9 + 7;

int main() {
  int n;
  cin >> n;
  vector<ll> dp(n + 1, 0);

  dp[0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int d = 1; d <= 6; d++) {
      if (i - d >= 0) {
        dp[i] += dp[i - d];
        dp[i] %= mod;
      }
    }
  }

  cout << dp.back() << endl;
}
