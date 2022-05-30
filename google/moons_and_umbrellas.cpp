#include <bits/stdc++.h>
using namespace std;

int X, Y;
int memo[2][1001];
bool ok[2][1001];
string str;

int dp(const char prev, const int i) {
  if (i == (int)str.size()) return 0;
  if (ok[prev == 'J'][i]) return memo[prev == 'J'][i];

  int res;

  const int j = X * (prev == 'C') + dp('J', i + 1);
  const int c = Y * (prev == 'J') + dp('C', i + 1);

  switch (str[i]) {
    case 'J':
      res = j;
      break;
    case 'C':
      res = c;
      break;
    default:
      res = min(c, j);
  }

  ok[prev == 'J'][i] = true;
  return memo[prev == 'J'][i] = res;
}

void solve() {
  memset(ok, 0, sizeof ok);
  cin >> X >> Y;
  cin >> str;

  int ans = INT_MAX;

  if (str.front() == '?') {
    ans = min(dp('C', 1), dp('J', 1));
  } else {
    ans = dp(str.front(), 1);
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;

  for (int t = 0; t < T; t++) {
    cout << "Case #" << t + 1 << ": ";
    solve();
  }
}
