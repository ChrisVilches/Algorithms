#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll memo[2001][21], items[2001], items_prefix_sum[2001];

ll round_cents(ll money) {
  ll unit = money % 10;

  if (unit < 5)
    money -= unit;
  else
    money += (10 - unit);
  return money;
}

ll sum_range(int l, int r) {
  return items_prefix_sum[r + 1] - items_prefix_sum[l];
}

ll dp(int n, int d) {
  if (n < 0) return 0;
  ll sum = round_cents(sum_range(0, n - 1));
  if (d == 0) return sum;

  if (memo[n][d] != -1) return memo[n][d];

  ll min_money = sum;

  for (int i = 0; i < n; i++) {
    ll with_divider =
        round_cents(dp(i, d - 1) + round_cents(sum_range(i, n - 1)));
    min_money = min(min_money, with_divider);
  }

  return memo[n][d] = min_money;
}

int main() {
  int n, d;
  while (scanf("%d %d", &n, &d) == 2) {
    memset(memo, -1, sizeof memo);
    items_prefix_sum[0] = 0;

    for (int i = 0; i < n; i++) {
      cin >> items[i];
      items_prefix_sum[i + 1] = items_prefix_sum[i] + items[i];
    }

    cout << dp(n, d) << endl;
  }
}
