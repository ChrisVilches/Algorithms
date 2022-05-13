#include <bits/stdc++.h>
using namespace std;

int graph[21];

void solve() {
  memset(graph, 0, sizeof graph);
  int N;
  cin >> N;

  for (int u = 0; u < N; u++) {
    int d;
    cin >> d;
    for (int j = 0; j < d; j++) {
      int v;
      cin >> v;
      v--;

      graph[u] |= 1 << v;
      graph[v] |= 1 << u;
    }
  }

  const int target = (1 << N) - 1;

  int ans = INT_MAX;

  for (int subset = 0; subset < (1 << N); subset++) {
    int curr_users = 0;
    int sum = 0;

    for (int u = 0; u < N; u++) {
      if ((subset & (1 << u)) == 0) continue;

      curr_users++;
      sum |= (1 << u);
      sum |= graph[u];
    }

    if (sum == target) {
      ans = min(ans, curr_users);
    }
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) solve();
}
