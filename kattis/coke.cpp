#include <bits/stdc++.h>

using namespace std;
#define INF 1000000

int memo[353][403][353];
int total_money;

int cokes(int C, int n5, int n10) {
  int n1 = total_money - (n5 * 5) - (n10 * 10);

  if (n1 < 0 || n5 < 0 || n10 < 0) return INF;
  if (C == 0) return 0;
  if (memo[C][n5][n10] != -1) return memo[C][n5][n10];

  int all1 = C * 8;
  int use1 = 8 + cokes(C - 1, n5, n10);
  int use1_5 = 4 + cokes(C - 1, n5 - 1, n10);
  int use5 = 2 + cokes(C - 1, n5 - 2, n10);
  int use10 = 1 + cokes(C - 1, n5, n10 - 1);
  int use1_10 = 4 + cokes(C - 1, n5 + 1, n10 - 1);

  return memo[C][n5][n10] = min({all1, use1, use1_5, use5, use10, use1_10});
}

void solve() {
  int C, n1, n5, n10;

  cin >> C >> n1 >> n5 >> n10;
  total_money = n1 + (5 * n5) + (10 * n10);
  cout << cokes(C, n5, n10) << endl;
}

int main() {
  int T;
  cin >> T;
  memset(memo, -1, sizeof memo);
  while (T--) solve();
}
