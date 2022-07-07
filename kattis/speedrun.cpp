#include <bits/stdc++.h>
using namespace std;

map<int, int> tasks;
int memo[24'001];

int dp(const int t) {
  if (~memo[t]) return memo[t];

  const auto it = tasks.lower_bound(t);
  if (it == tasks.end()) return 0;

  const int take = 1 + dp(it->second);
  const int skip = dp(t + 1);

  return memo[t] = max(take, skip);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int G, N;

  while (cin >> G >> N) {
    tasks.clear();
    memset(memo, -1, sizeof memo);

    for (int i = 0; i < N; i++) {
      int t1, t2;
      cin >> t1 >> t2;

      if (!tasks.count(t1) || tasks[t1] > t2) tasks[t1] = t2;
    }

    cout << (dp(0) >= G ? "YES" : "NO") << endl;
  }
}
