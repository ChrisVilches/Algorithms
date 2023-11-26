#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> Graph;

struct Point {
  double x, y;
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
};

int R, H;
const double SPEED = 10;

Point robots[201], holes[201];

bool bpm(const Graph& g, const int u, vector<bool>& visited, vector<int>& match) {
  for (const int v : g[u]) {
    if (visited[v]) continue;
    visited[v] = true;

    if (match[v] == -1 || bpm(g, match[v], visited, match)) {
      match[v] = u;
      return true;
    }
  }

  return false;
}

int max_bipartite_matching(const Graph& g, const int match_set_size) {
  vector<int> match(match_set_size, -1);
  vector<bool> visited(match_set_size);
  int result = 0;
  for (int u = 0; u < (int)g.size(); u++) {
    fill(visited.begin(), visited.end(), false);
    result += bpm(g, u, visited, match);
  }
  return result;
}

int can_escape(const int seconds) {
  Graph g(R);

  for (int i = 0; i < R; i++)
    for (int j = 0; j < H; j++)
      if (robots[i].dist(holes[j]) / SPEED <= seconds) g[i].push_back(j);

  return max_bipartite_matching(g, H);
}

int main() {
  int t = 1;

  while (cin >> R && R) {
    for (int i = 0; i < R; i++) cin >> robots[i].x >> robots[i].y;

    cin >> H;
    for (int i = 0; i < H; i++) cin >> holes[i].x >> holes[i].y;

    cout << "Scenario " << t++ << endl;

    for (const int s : {5, 10, 20}) {
      const int result = can_escape(s);
      cout << "In " << s << " seconds " << result << " robot(s) can escape" << endl;
    }

    cout << endl;
  }
}
