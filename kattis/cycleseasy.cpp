#include <bits/stdc++.h>
using namespace std;

int forbidden[11][11];

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    memset(forbidden, 0, sizeof(forbidden));
    int n, k;
    cin >> n >> k;
    while (k--) {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      forbidden[u][v] = 1;
      forbidden[v][u] = 1;
    }

    vector<bool> visited(n, false);
    int curr_size = 0;
    int ans = 0;

    const function<void(int)> recur = [&](const int u) {
      visited[u] = true;
      curr_size++;

      if (curr_size == n && !forbidden[u][0]) {
        ans++;
      } else {
        for (int v = 0; v < n; v++) {
          if (visited[v] || forbidden[u][v]) continue;
          recur(v);
        }
      }

      visited[u] = false;
      curr_size--;
    };

    recur(0);

    cout << "Case #" << t << ": " << (ans / 2) % 9901 << endl;
  }
}
