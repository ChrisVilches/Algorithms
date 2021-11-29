#include <bits/stdc++.h>

using namespace std;

int N;
short segments[201];
int memo[201];

int dp(int n) {
  if (n == N) return 0;
  if (memo[n] != -1) return memo[n];

  int ans = 0;
  int zeros = 0;
  int ones = 0;

  for (int i = n; i < N; i++) {
    if (segments[i] == 0)
      zeros++;
    else
      ones++;

    int curr_length = i - n + 1;

    if (zeros >= ones) curr_length = 0;

    int cut = curr_length + dp(i + 1);
    int dont_cut = curr_length;

    ans = max({ans, cut, dont_cut});
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
