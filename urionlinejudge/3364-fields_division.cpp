#include <bits/stdc++.h>
using namespace std;

int N, M;
short result[3 * 100001];

void solve() {
  memset(result, -1, sizeof result);

  vector<vector<int>> graph(N);

  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;

    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  result[N - 1] = 0;
  result[N - 2] = 1;

  queue<int> q;

  q.push(N - 2);

  while (!q.empty()) {
    const int u = q.front();
    q.pop();

    for (const int v : graph[u]) {
      if (~result[v]) continue;
      result[v] = result[u];
      q.push(v);
    }
  }

  for (int i = 0; i < N; i++) {
    if (~result[i]) continue;
    result[i] = 0;
  }

  for (int i = 0; i < N; i++) {
    cout << (result[i] ? 'B' : 'A');
  }

  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> M) solve();
}
