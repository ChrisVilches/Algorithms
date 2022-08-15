#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  double operator*(const Point& p) const { return x * p.x + y * p.y; }
  Point to(const Point& p) const { return p - *this; }
  double magnitude() const { return hypot(x, y); }
  double dist(const Point& p) const { return to(p).magnitude(); }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
};

struct Segment {
  Point p, q;
  Point to_vec() const { return p.to(q); }
  double dist(const Point& r) const {
    if ((r - p) * to_vec() < 0)
      return r.dist(p);
    else if ((r - q) * to_vec() > 0)
      return r.dist(q);
    return fabs(to_vec().cross(r - p)) / p.dist(q);
  }
};

struct Circle {
  double x, y, radius;

  Circle operator-(const Point& p) const { return {x - p.x, y - p.y, radius}; }

  bool intersects(const Circle& c) const {
    const double center_dist = hypot(x - c.x, y - c.y);
    const double radius_sum = radius + c.radius;
    return center_dist <= radius_sum;
  }

  pair<Point, Point> points_of_tangency_from_origin() const {
    const double a = radius;
    const double b = hypot(x, y);
    const double th = acos(a / b);
    const double d = atan2(-y, -x);
    const double d1 = d + th, d2 = d - th;
    return {{x + a * cos(d1), y + a * sin(d1)}, {x + a * cos(d2), y + a * sin(d2)}};
  }
};

struct DisjointSets {
  DisjointSets(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }

  int find(const int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rank[x] == rank[y]) rank[y]++;
  }

 private:
  vector<int> parent, rank;
};

int B, N, M;
vector<Segment> edges;
Point informers[1001];
Circle radars[31];
vector<vector<Circle>> radar_groups;

void read_edges() {
  if (B == 0) return;
  vector<Point> v(B);
  for (auto& p : v) cin >> p.x >> p.y;
  v.push_back(v.front());
  edges.clear();
  for (int i = 0; i < B; i++) edges.push_back({v[i], v[i + 1]});
}

void create_radar_groups() {
  DisjointSets ds(M);
  for (int i = 0; i < M; i++)
    for (int j = i + 1; j < M; j++)
      if (radars[i].intersects(radars[j])) ds.merge(i, j);

  map<int, vector<Circle>> groups_map;
  for (int i = 0; i < M; i++) groups_map[ds.find(i)].push_back(radars[i]);
  radar_groups.clear();
  for (const auto& [_, radars] : groups_map) radar_groups.push_back(radars);
}

double calculate_coefficient(const int idx) {
  double value = DBL_MAX;
  for (const Segment& s : edges) value = min(value, s.dist(informers[idx]));
  return value;
}

bool trapped_inside(const Point& point, vector<Circle> radars) {
  for (auto& c : radars) c = c - point;
  for (const auto& c : radars)
    if (hypot(c.x, c.y) < c.radius) return true;

  vector<pair<Point, int>> events;

  int curr = 0;

  for (const auto& c : radars) {
    const auto [p, q] = c.points_of_tangency_from_origin();
    if (q < p) curr++;
    events.emplace_back(p, 1);
    events.emplace_back(q, -1);
  }

  sort(events.begin(), events.end());

  for (const auto& [_, d] : events) {
    curr += d;
    if (curr == 0) return false;
  }

  return true;
}

bool can_access(const Point& p) {
  for (const vector<Circle>& group : radar_groups)
    if (trapped_inside(p, group)) return false;

  return true;
}

int main() {
  while (cin >> B) {
    read_edges();
    cin >> N;
    for (int i = 0; i < N; i++) cin >> informers[i].x >> informers[i].y;
    cin >> M;
    for (int i = 0; i < M; i++) cin >> radars[i].x >> radars[i].y >> radars[i].radius;

    if (B == 0 && N == 0 && M == 0) break;

    create_radar_groups();

    int idx = -1;
    double highest = DBL_MIN;

    for (int i = 0; i < N; i++) {
      if (!can_access(informers[i])) continue;

      const double coefficient = calculate_coefficient(i);

      if (coefficient > highest) {
        idx = i;
        highest = coefficient;
      }
    }

    if (idx == -1) {
      cout << "Mission impossible" << endl;
    } else {
      cout << "Contact informer " << idx + 1 << endl;
    }
  }
}
