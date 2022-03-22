#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = INT_MAX;

struct Edge {
  int u, v;
  ll w;
};

vector<ll> bellman_ford(const int V, const vector<Edge>& edges, const int src) {
  vector<ll> dist(V, INF);

  dist[src] = 0;

  int iter = V - 1;

  while (iter--)
    for (const auto [u, v, w] : edges) dist[v] = min(dist[v], dist[u] + w);

  for (const auto [u, v, w] : edges)
    if (dist[u] + w < dist[v]) return vector<ll>();

  return dist;
}

void solve() {
  int N, M;
  cin >> N >> M;
  vector<Edge> edges(M);

  for (int i = 0; i < M; i++) {
    cin >> edges[i].u >> edges[i].v >> edges[i].w;
  }

  const auto dist = bellman_ford(N, edges, 0);

  cout << (dist.empty() ? "possible" : "not possible") << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) solve();
}
