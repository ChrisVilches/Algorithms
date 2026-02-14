#include <bits/stdc++.h>
using namespace std;

const int inf = 1e7;
string s;
int n;
int memo[200'007][3];

int steps(const int form) {
  if (form < 0 || form > 2) return inf;
  return form == 0 ? 1 : 2;
}

int dp(const int idx, const int form) {
  if (form < 0 || form > 2) return inf;
  if (idx == n - 1) return 0;
  if (~memo[idx][form]) return memo[idx][form];

  int res = inf;

  switch (s[idx]) {
    case '.':
      res = steps(form) + dp(idx + 1, form);
      break;
    case 'S':
      res = steps(form - 1) + dp(idx + 1, form - 1);
      break;
    case '?':
      const int take = steps(form + 1) + dp(idx + 1, form + 1);
      const int dont_take = steps(form) + dp(idx + 1, form);

      res = min(take, dont_take);
      break;
  }

  return memo[idx][form] = res;
}

int main() {
  while (cin >> n) {
    memset(memo, -1, sizeof memo);
    cin >> s;
    const int ans = min({dp(0, 0), dp(0, 1), dp(0, 2)});

    if (ans >= inf) {
      cout << -1 << endl;
    } else {
      cout << ans << endl;
    }
  }
}
