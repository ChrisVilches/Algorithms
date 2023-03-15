#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  bool operator==(const Point p) const { return x == p.x && y == p.y; }
  Point operator-(const Point p) const { return Point{x - p.x, y - p.y}; }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const ll cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : cross > 0;
}

struct Segment {
  Point p, q;
  bool is_ceil() const { return p.x < q.x; }
  bool contains(const ll x) const { return p.x <= x && x <= q.x; }
  bool is_horizontal() const { return p.y == q.y; }
  bool move_right() const { return p.y < q.y; }
  Point up_endpoint() const { return p.y < q.y ? q : p; }
  bool point_below(const Point r) const { return orientation(p, q, r) < 0; }
};

enum { SKY = -1, STUCK = -2 };
int N, B;
vector<Point> polygon, balls;
int next_edge[1003];

int find_lowest(const Point below) {
  int idx = SKY;
  double min_y = 1e9;

  for (int i = 0; i < N; i++) {
    const Point p = polygon[i];
    const Point q = polygon[(i + 1) % N];
    const Segment edge{p, q};
    if (!edge.is_ceil()) continue;
    if (!edge.contains(below.x)) continue;
    if (!edge.point_below(below)) continue;

    const ll dx = below.x - p.x;
    const double slope = (p.y - q.y) / (double)(p.x - q.x);
    const double curr_y = p.y + dx * slope;

    if (curr_y < min_y) {
      idx = i;
      min_y = curr_y;
    }
  }

  return idx;
}

Segment edge_at(const int i) {
  return Segment{polygon[(i + N) % N], polygon[(i + 1 + N) % N]};
}

void build_next_edge() {
  for (int i = 0; i < N; i++) {
    const Segment edge = edge_at(i);

    if (!edge.is_ceil()) continue;
    if (edge.is_horizontal()) {
      next_edge[i] = STUCK;
      continue;
    }

    const int dir = edge.move_right() ? 1 : -1;
    const Segment adj_edge = edge_at(i + dir);

    if (adj_edge.is_ceil()) {
      if (edge.up_endpoint() == adj_edge.up_endpoint()) {
        next_edge[i] = STUCK;
      } else {
        next_edge[i] = (i + dir + N) % N;
      }
    } else {
      if (edge.point_below(dir == 1 ? adj_edge.q : adj_edge.p)) {
        next_edge[i] = STUCK;
      } else {
        next_edge[i] = find_lowest(edge.up_endpoint());
      }
    }
  }
}

bool stuck(const Point ball) {
  int idx = find_lowest(ball);

  if (idx == SKY) {
    return false;
  }

  while (next_edge[idx] != STUCK) {
    if (next_edge[idx] == SKY) return false;
    idx = next_edge[idx];
  }

  return edge_at(idx).up_endpoint().y <= 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> B) {
    polygon.resize(N);
    balls.resize(B);

    for (Point& p : polygon) cin >> p.x >> p.y;
    for (Point& b : balls) {
      cin >> b.x;
      b.y = -1e6;
    }

    build_next_edge();

    int ans = 0;

    for (const Point b : balls) {
      ans += stuck(b);
    }

    cout << ans << endl;
  }
}
