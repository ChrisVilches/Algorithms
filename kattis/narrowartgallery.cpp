#include <bits/stdc++.h>
using namespace std;

int N, K;
int rooms[201][2];
int memo[201][3][201];
constexpr int INF = 1e6;

int dp(const int i, const int prev_blocked, const int k) {
  if (k < 0) return INF;
  if (i == N) return k == 0 ? 0 : INF;

  if (~memo[i][prev_blocked][k]) return memo[i][prev_blocked][k];

  int loss = dp(i + 1, 0, k);

  if (prev_blocked == 0 || prev_blocked == 1) {
    loss = min(loss, rooms[i][0] + dp(i + 1, 1, k - 1));
  }

  if (prev_blocked == 0 || prev_blocked == 2) {
    loss = min(loss, rooms[i][1] + dp(i + 1, 2, k - 1));
  }

  return memo[i][prev_blocked][k] = loss;
}

int main() {
  while (cin >> N >> K && N) {
    memset(memo, -1, sizeof memo);

    int total_value = 0;

    for (int i = 0; i < N; i++) {
      cin >> rooms[i][0] >> rooms[i][1];
      total_value += rooms[i][0] + rooms[i][1];
    }

    cout << total_value - dp(0, 0, K) << endl;
  }
}
