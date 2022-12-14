#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1007;

bool grid[MAX_N][MAX_N];
int horizontal[MAX_N][MAX_N], vertical[MAX_N][MAX_N];
pair<int, int> dp[MAX_N][MAX_N];

bool cmp(const pair<int, int> s1, const pair<int, int> s2) {
  return s1.first + s1.second < s2.first + s2.second;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int R, C;

  while (cin >> R >> C) {
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        char c;
        cin >> c;
        grid[i][j] = c == '.';
      }
    }

    for (int i = 0; i < R; i++) {
      int count = 0;
      for (int j = 0; j < C; j++) {
        count = grid[i][j] ? count + 1 : 0;
        horizontal[i][j] = count;
      }
    }

    for (int j = 0; j < C; j++) {
      int count = 0;
      for (int i = 0; i < R; i++) {
        count = grid[i][j] ? count + 1 : 0;
        vertical[i][j] = count;
      }
    }

    for (int i = 0; i < R; i++) dp[i][0] = {vertical[i][0], 1};
    for (int j = 0; j < C; j++) dp[0][j] = {1, horizontal[0][j]};

    for (int i = 1; i < R; i++) {
      for (int j = 1; j < C; j++) {
        const auto [r, c] = dp[i - 1][j - 1];
        const pair<int, int> prev{min(1 + r, vertical[i][j]),
                                  min(1 + c, horizontal[i][j])};

        array<pair<int, int>, 3> sol{prev, {1, horizontal[i][j]}, {vertical[i][j], 1}};
        dp[i][j] = *max_element(sol.begin(), sol.end(), cmp);
      }
    }

    int ans = 0;

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        const auto [r, c] = dp[i][j];
        ans = max(ans, 2 * (r + c) - 1);
      }
    }

    cout << ans << endl;
  }
}
