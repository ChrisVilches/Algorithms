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

  for (int i = 0; i < N; i++) {
    sort(graph[i].rbegin(), graph[i].rend());
  }

  result[N - 1] = 0;
  result[N - 2] = 1;

  queue<int> q1, q2;

  q1.push(N - 1);
  q2.push(N - 2);

  queue<int>* q;

  while (!q1.empty() || !q2.empty()) {
    if (q1.empty())
      q = &q2;
    else if (q2.empty())
      q = &q1;
    else
      q = q1.front() > q2.front() ? &q2 : &q1;

    const int u = q->front();
    q->pop();

    for (const int v : graph[u]) {
      if (result[v] != -1) continue;
      result[v] = result[u];
      q->push(v);
    }
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
