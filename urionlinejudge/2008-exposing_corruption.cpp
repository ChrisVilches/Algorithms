#include <bits/stdc++.h>

using namespace std;

int D, P, R, B;
vector<vector<int>> graph;

int items;
int cost[201];
int memo[201][10007][2];
bool visited[201];

struct Component {
  int d, p, cost;
  Component() : d(0), p(0), cost(0) {}

  int buy_value() { return max(d, p); }
  int not_buy_value(bool for_d) { return for_d ? d : p; }

  int weight(bool for_d) {
    if (for_d)
      return d >= p ? 0 : cost;
    else
      return p >= d ? 0 : cost;
  }
} components[200];

void dfs(int i) {
  if (visited[i]) return;
  visited[i] = true;

  components[items].d += i < D;
  components[items].p += i >= D;
  components[items].cost += cost[i];

  for (int v : graph[i]) dfs(v);
}

int dp(bool d, int n, int k) {
  if (k < 0) return -1e9;
  if (n < 0) return 0;
  if (~memo[n][k][d]) return memo[n][k][d];

  int buy_value = components[n].buy_value();
  int not_buy_value = components[n].not_buy_value(d);
  int total_cost = components[n].weight(d);

  int buy = buy_value + dp(d, n - 1, k - total_cost);
  int not_buy = not_buy_value + dp(d, n - 1, k);

  return memo[n][k][d] = max(buy, not_buy);
}

void solve() {
  memset(memo, -1, sizeof memo);
  fill(components, components + 200, Component());
  memset(visited, false, sizeof visited);
  graph.assign(D + P, vector<int>());

  for (int i = 0; i < D + P; i++) scanf("%d", &cost[i]);

  for (int i = 0; i < R; i++) {
    int d, p;
    cin >> d >> p;
    d--;
    p--;
    graph[d].push_back(D + p);
    graph[D + p].push_back(d);
  }

  items = 0;

  for (int i = 0; i < (int)graph.size(); i++) {
    dfs(i);
    items++;
  }

  printf("%d %d\n", dp(true, items - 1, B), dp(false, items - 1, B));
}

int main() {
  while (scanf("%d %d %d %d", &D, &P, &R, &B) == 4) solve();
}
