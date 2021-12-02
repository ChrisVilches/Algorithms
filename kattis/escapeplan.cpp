#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> graph;

struct Point {
  double x, y;
  double dist(const Point& p) const {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  }
};

int R, H;
const double SPEED = 10;
int match[10000];
bool visited[10000];

Point robots[201], holes[201];

bool bpm(graph& g, int u) {
  for (int v : g[u])
    if (!visited[v]) {
      visited[v] = true;
      if (match[v] < 0 || bpm(g, match[v])) {
        match[v] = u;
        return true;
      }
    }
  return false;
}

int max_bipartite_matching(graph& g) {
  memset(match, -1, sizeof match);
  int result = 0;
  for (int u = 0; u < (int)g.size(); u++) {
    memset(visited, 0, sizeof visited);
    result += bpm(g, u);
  }
  return result;
}

int can_escape(int seconds) {
  graph g(R);

  for (int i = 0; i < R; i++)
    for (int j = 0; j < H; j++)
      if (robots[i].dist(holes[j]) / SPEED <= seconds) g[i].push_back(j);

  return max_bipartite_matching(g);
}

int main() {
  int t = 1;

  while (scanf("%d", &R) == 1) {
    if (R == 0) break;

    for (int i = 0; i < R; i++) cin >> robots[i].x >> robots[i].y;

    cin >> H;
    for (int i = 0; i < H; i++) cin >> holes[i].x >> holes[i].y;

    printf("Scenario %d\n", t++);
    printf("In 5 seconds %d robot(s) can escape\n", can_escape(5));
    printf("In 10 seconds %d robot(s) can escape\n", can_escape(10));
    printf("In 20 seconds %d robot(s) can escape\n", can_escape(20));
    printf("\n");
  }
}
