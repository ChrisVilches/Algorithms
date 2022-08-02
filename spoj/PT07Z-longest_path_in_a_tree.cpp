#include <bits/stdc++.h>
using namespace std;

bool visited[10001];
vector<vector<int>> tree;

pair<int, int> find_max_dist(const int root) {
  memset(visited, 0, sizeof visited);

  queue<pair<int, int>> q;
  q.emplace(root, 0);

  int node = 0;
  int max_dist = 0;

  while (!q.empty()) {
    const auto [u, dist] = q.front();
    q.pop();

    if (dist > max_dist) {
      node = u;
      max_dist = dist;
    }

    visited[u] = true;

    for (const int v : tree[u]) {
      if (visited[v]) continue;
      q.emplace(v, dist + 1);
    }
  }

  return {node, max_dist};
}

int main() {
  int N;
  cin >> N;

  tree.assign(N, vector<int>());

  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;

    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  const auto [u, _] = find_max_dist(0);
  const auto [__, dist] = find_max_dist(u);

  cout << dist << endl;
}
