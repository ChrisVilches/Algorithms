#include <bits/stdc++.h>
using namespace std;

int memo[503][503];

int dp(const int a, const int b) {
  if (a == b) return 0;
  if (a == 1 || b == 1) return max(a, b) - 1;
  if (~memo[a][b]) return memo[a][b];
  int res = 1e7;

  for (int i = 1; i < a / 2 + 1; i++) {
    res = min(res, 1 + dp(i, b) + dp(a - i, b));
  }

  for (int i = 1; i < b / 2 + 1; i++) {
    res = min(res, 1 + dp(a, i) + dp(a, b - i));
  }

  return memo[a][b] = res;
}

int main() {
  int a, b;
  memset(memo, -1, sizeof memo);
  while (cin >> a >> b) {
    cout << dp(a, b) << endl;
  }
}
