#include <bits/stdc++.h>
using namespace std;

double A, B;
int N;
tuple<double, double, int> intervals[20'007];
int next_idx[20'007];
int memo[20'007];

int dp(const int i) {
  if (~memo[i]) return memo[i];

  const auto [from, to, _] = intervals[i];
  if (B <= to) return 1;

  int res = 30'000;

  for (int j = i + 1; j < N; j++) {
    const auto [a, b, _] = intervals[j];
    if (a <= from) continue;
    if (to < a) continue;
    if (b <= from) continue;

    const int new_res = 1 + dp(j);

    if (new_res <= res) {
      res = new_res;
      next_idx[i] = j;
    }
  }

  return memo[i] = res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> A >> B) {
    memset(memo, -1, sizeof memo);

    cin >> N;

    for (int i = 0; i < N; i++) {
      double a, b;
      cin >> a >> b;
      intervals[i] = {a, b, i};
    }

    int idx = 0;

    int amount = INT_MAX;

    sort(intervals, intervals + N);

    for (int i = 0; i < N; i++) {
      const auto [from, to, _] = intervals[i];
      if (A < from) continue;
      if (to < A) continue;

      if (dp(i) < amount) {
        idx = i;
        amount = dp(i);
      }
    }

    if (amount > 20'000) {
      cout << "impossible" << endl;
      continue;
    }

    cout << amount << endl;

    for (int it = 0; it < amount; it++) {
      cout << get<2>(intervals[idx]) << ' ';
      idx = next_idx[idx];
    }

    cout << endl;
  }
}
