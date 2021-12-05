#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define V 507
ll g[V][V], rgraph[V][V];
bool visited[V];

int N, M, S, T;

vector<vector<int>> edges;

bool bfs(ll (&rgraph)[V][V], int s, int t, array<int, V>& parent) {
  memset(visited, 0, sizeof(visited));
  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : edges[u]) {
      if (!visited[v] && rgraph[u][v] > 0) {
        if (v == t) {
          parent[v] = u;
          return true;
        }
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return false;
}

ll ford_fulkerson(ll (&g)[V][V], ll (&rgraph)[V][V], int s, int t) {
  int u, v;
  array<int, V> parent;
  ll max_flow = 0;

  memcpy(rgraph, g, sizeof g);

  while (bfs(rgraph, s, t, parent)) {
    ll path_flow = LONG_LONG_MAX;
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, (ll)rgraph[u][v]);
    }

    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      rgraph[u][v] -= path_flow;
      rgraph[v][u] += path_flow;
    }

    max_flow += path_flow;
  }

  return max_flow;
}

void solve() {
  memset(g, 0, sizeof g);
  memset(rgraph, 0, sizeof rgraph);

  edges.assign(N, vector<int>());

  for (int i = 0; i < M; i++) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    g[u][v] = c;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  ll flow = ford_fulkerson(g, rgraph, S, T);

  vector<tuple<int, int, ll>> edges;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      ll x = g[i][j] - rgraph[i][j];
      if (x <= 0) continue;
      edges.push_back(make_tuple(i, j, x));
    }

  printf("%d %lld %ld\n", N, flow, edges.size());

  for (tuple<int, int, ll>& t : edges)
    printf("%d %d %lld\n", get<0>(t), get<1>(t), get<2>(t));
}

int main() {
  while (scanf("%d %d %d %d", &N, &M, &S, &T) == 4) solve();
}
