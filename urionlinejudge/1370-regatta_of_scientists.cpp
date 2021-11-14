#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<pair<int, double>>> graph_t;
typedef pair<double, int> pdi;

int node_count = 0;

struct Point {
  int x, y;
  int node_idx;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}
  void set_node_idx() {
    node_idx = node_count;
    node_count++;
  }
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}

  Point endpoint(int n) { return n == 0 ? p : q; }

  int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
  }

  bool intersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    return o1 != o2 && o3 != o4;
  }

  bool intersect(Segment& s) { return intersect(p, q, s.p, s.q); }

  inline double length() { return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2)); }
};

int N;

Point start, goal;
vector<Segment> obstacle;
graph_t graph;

bool route_valid(Segment& s, int except1, int except2) {
  for (int i = 0; i < (int)obstacle.size(); i++) {
    if (i == except1 || i == except2) continue;
    if (s.intersect(obstacle[i])) return false;
  }
  return true;
}

double dijkstra(graph_t& graph) {
  vector<double> dist(graph.size(), 10e9);

  priority_queue<pdi, vector<pdi>, greater<pdi>> q;

  q.push(make_pair(start.node_idx, 0));
  dist[start.node_idx] = 0;

  while (!q.empty()) {
    pair<int, int> u = q.top();
    q.pop();
    auto neighbors = graph[u.first];
    for (pair<int, double> neighbor : neighbors) {
      int v = neighbor.first;
      double alt = dist[u.first] + neighbor.second;
      if (alt < dist[v]) {
        dist[v] = alt;
        q.push(make_pair(v, alt));
      }
    }
  }

  return dist[goal.node_idx];
}

void add_edges_from_start() {
  for (int i = 0; i < N; i++)
    for (int e = 0; e < 2; e++) {
      Segment line(start, obstacle[i].endpoint(e));

      if (route_valid(line, i, -1))
        graph[start.node_idx].push_back(
            make_pair(obstacle[i].endpoint(e).node_idx, line.length()));
    }

  Segment line_start_goal(start, goal);

  if (route_valid(line_start_goal, -1, -1))
    graph[start.node_idx].push_back(
        make_pair(goal.node_idx, line_start_goal.length()));
}

void add_edges_from_segments() {
  for (int i = 0; i < N; i++) {
    Segment& obsi = obstacle[i];
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      Segment& obsj = obstacle[j];

      for (int e = 0; e < 2; e++)
        for (int f = 0; f < 2; f++) {
          Segment line(obsi.endpoint(e), obsj.endpoint(f));

          if (route_valid(line, i, j))
            graph[obsi.endpoint(e).node_idx].push_back(
                make_pair(obsj.endpoint(f).node_idx, line.length()));
        }
    }

    for (int e = 0; e < 2; e++) {
      Segment line(obsi.endpoint(e), goal);
      if (route_valid(line, i, -1))
        graph[obsi.endpoint(e).node_idx].push_back(
            make_pair(goal.node_idx, line.length()));
    }
  }
}

void solve() {
  obstacle.clear();
  node_count = 0;

  start.set_node_idx();
  goal.set_node_idx();

  for (int i = 0; i < N; i++) {
    Segment s;
    cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
    s.p.set_node_idx();
    s.q.set_node_idx();
    obstacle.push_back(s);
  }

  graph = vector<vector<pair<int, double>>>(2 + N * 2);
  add_edges_from_start();
  add_edges_from_segments();

  printf("%.2f\n", dijkstra(graph));
}

int main() {
  while (scanf("%d %d %d %d %d", &start.x, &start.y, &goal.x, &goal.y, &N) ==
         5) {
    if (!(start.x || start.y || goal.x || goal.y || N)) break;
    solve();
  }
}
