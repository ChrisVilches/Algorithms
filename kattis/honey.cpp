#include <bits/stdc++.h>
using namespace std;

int memo[30][30][15];
const int di[6]{-1, -1, 0, 0, 1, 1};
const int dj[6]{0, 1, -1, 1, -1, 0};

int dp(const int i, const int j, const int steps) {
  if (steps < 0) return 0;
  if (steps == 0 && i == 15 && j == 15) return 1;
  auto& m = memo[i][j][steps];
  if (~m) return m;

  int res = 0;

  for (int d = 0; d < 6; d++) {
    const int i2 = i + di[d];
    const int j2 = j + dj[d];
    res += dp(i2, j2, steps - 1);
  }

  return m = res;
}

int main() {
  int t, n;
  cin >> t;
  memset(memo, -1, sizeof memo);
  while (t--) {
    cin >> n;
    cout << dp(15, 15, n) << endl;
  }
}
