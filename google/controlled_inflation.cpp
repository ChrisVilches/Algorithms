#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll products[1001][101];
ll memo[1031][201], min_prod[1001], max_prod[1001];
int N, P;

ll dp(const int n, const int init) {
  if (~memo[n][init]) return memo[n][init];
  if (n == N) return 0;

  const ll part1 = products[n][init] - min_prod[n];
  const ll part2 = max_prod[n] - products[n][init];

  const ll min_part = min(part1, part2);
  const ll max_part = max(part1, part2);

  const ll all = max_part + 2 * min_part;

  if (n == N - 1) {
    return memo[n][init] = all;
  }

  ll ans = LONG_LONG_MAX;

  ll last_product;

  if (abs(products[n][init] - min_prod[n]) > abs(products[n][init] - max_prod[n])) {
    last_product = min_prod[n];
  } else {
    last_product = max_prod[n];
  }

  for (int p = 0; p < P; p++) {
    const ll diff = abs(last_product - products[n + 1][p]);
    ans = min(ans, all + diff + dp(n + 1, p));
  }

  return memo[n][init] = ans;
}

void solve() {
  memset(memo, -1, sizeof memo);
  cin >> N >> P;

  for (int i = 0; i < N; i++) {
    min_prod[i] = LONG_LONG_MAX;
    max_prod[i] = LONG_LONG_MIN;

    for (int j = 0; j < P; j++) {
      cin >> products[i][j];

      min_prod[i] = min(min_prod[i], products[i][j]);
      max_prod[i] = max(max_prod[i], products[i][j]);
    }
  }

  for (int i = 0; i < P; i++) {
    if (min_prod[0] == products[0][i]) {
      cout << dp(0, i) + min_prod[0] << endl;
      break;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
