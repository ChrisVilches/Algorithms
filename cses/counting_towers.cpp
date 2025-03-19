#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9 + 7;
const int max_n = 1'000'007;

array<ll, max_n> dp;

int main() {
  int t, n;
  cin >> t;

  ll sum1 = 0;
  ll sum2 = 0;
  ll pow3 = 1;

  for (int i = 1; i < max_n; i++) {
    dp[i] = (sum1 + sum2 + pow3 + 1) % mod;

    sum1 = (3 * sum1 + dp[i]) % mod;
    sum2 = (sum2 + dp[i] % mod);
    pow3 = (pow3 * 3) % mod;
  }

  while (t--) {
    cin >> n;
    cout << dp[n] << endl;
  }
}
