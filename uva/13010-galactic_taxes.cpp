#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
typedef pair<double, int> pdi;
int N, M;
double dist[1001];

vector<vector<pair<int, pii>>> graph;

double dijkstra(double t) {
  fill(dist, dist + N, 1e10);
  priority_queue<pdi, vector<pdi>, greater<pdi>> q;

  q.push(make_pair(0, 0));
  dist[0] = 0;

  while (!q.empty()) {
    pair<double, int> u = q.top();
    q.pop();
    for (pair<int, pii>& neighbor : graph[u.second]) {
      int v = neighbor.first;
      double alt =
          dist[u.second] + (neighbor.second.first * t + neighbor.second.second);
      if (alt < dist[v]) {
        dist[v] = alt;
        q.push(make_pair(alt, v));
      }
    }
  }

  return dist[N - 1];
}

int main() {
  scanf("%d %d", &N, &M);
  graph.assign(N, vector<pair<int, pii>>());

  while (M--) {
    int source, target, a, b;
    scanf("%d %d %d %d", &source, &target, &a, &b);
    source--;
    target--;

    graph[source].push_back({target, {a, b}});
    graph[target].push_back({source, {a, b}});
  }

  double left = 0;
  double right = 60 * 24;
  int iters = 80;

  while (iters--) {
    double third = (right - left) / 3;
    double t1 = left + third;
    double t2 = right - third;

    if (dijkstra(t1) < dijkstra(t2))
      left = t1;
    else
      right = t2;
  }

  printf("%0.5f\n", dijkstra(left));
}
