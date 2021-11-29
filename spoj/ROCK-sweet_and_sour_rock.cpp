#include <bits/stdc++.h>

using namespace std;

int N;
short segments[201];
int memo[201];

int dp(int n) {
  if (n == N) return 0;
  if (memo[n] != -1) return memo[n];

  int ans = 0;
  int sweetness = 0;

  for (int i = n; i < N; i++) {
    sweetness += segments[i] ? 1 : -1;

    int curr_length = sweetness > 0 ? i - n + 1 : 0;

    ans = max(ans, curr_length + dp(i + 1));
  }

  return memo[n] = ans;
}

void solve() {
  memset(memo, -1, sizeof memo);

  cin >> N;
  for (int i = 0; i < N; i++) {
    char c;
    scanf(" %c", &c);
    segments[i] = c == '1';
  }

  cout << dp(0) << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
