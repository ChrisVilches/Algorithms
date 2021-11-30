#include <bits/stdc++.h>

using namespace std;

int N;
int nums[201];
int memo[203][203][203];
const int NONE = 202;
const int INF = 1e5;

int dp(int n, int last_asc, int last_desc) {
  if (n == -1) return 0;
  if (~memo[n][last_asc][last_desc]) return memo[n][last_asc][last_desc];

  int dont_paint = 1 + dp(n - 1, last_asc, last_desc);
  int paint_asc = INF;
  int paint_desc = INF;

  if (last_asc == NONE || nums[n] > nums[last_asc])
    paint_asc = dp(n - 1, n, last_desc);

  if (last_desc == NONE || nums[n] < nums[last_desc])
    paint_desc = dp(n - 1, last_asc, n);

  return memo[n][last_asc][last_desc] =
             min({dont_paint, paint_asc, paint_desc});
}

void solve() {
  memset(memo, -1, sizeof memo);
  for (int i = 0; i < N; i++) {
    cin >> nums[i];
  }

  cout << dp(N - 1, NONE, NONE) << endl;
}

int main() {
  while (scanf("%d", &N) == 1 && N != -1) solve();
}
