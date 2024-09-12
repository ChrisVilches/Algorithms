#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int max_n = 2600;
ll memo[61][101][max_n];

ll dp(const int h, const int curr, const int remaining) {
  if (curr < 1 || remaining < 0 || h <= 0) return 0;
  if (h == 1) return 1;
  auto& m = memo[h][curr][remaining];
  if (~m) return m;

  const ll plus = dp(h - 1, curr + 1, remaining - (curr + 1));
  const ll minus = dp(h - 1, curr - 1, remaining - (curr - 1));

  return m = plus + minus;
}

int main() {
  int t;
  cin >> t;
  memset(memo, -1, sizeof memo);
  while (t--) {
    int n, h, m;
    cin >> n >> h >> m;
    n = min(n, max_n);
    cout << dp(h, m, n - m) << endl;
  }
}
