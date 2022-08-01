#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point& p) const { return x * p.y - y * p.x; }
  ll operator*(const Point& p) const { return x * p.x + y * p.y; }
  bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const ll cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : cross > 0;
}

struct Segment {
  Point p, q;

  bool intersects(const Segment& s) const {
    const short o1 = orientation(p, q, s.p), o2 = orientation(p, q, s.q);
    const short o3 = orientation(s.p, s.q, p), o4 = orientation(s.p, s.q, q);

    if (o1 * o2 == 0) return contains(s.p) || contains(s.q);
    if (o3 * o4 == 0) return s.contains(p) || s.contains(q);

    return o1 * o2 < 0 && o3 * o4 < 0;
  }

  bool operator<(const Segment& s) const {
    const int l = max(min(p.x, q.x), min(s.p.x, s.q.x));
    const int r = min(max(p.x, q.x), max(s.p.x, s.q.x));
    const long double x = (l + r) / 2.0;
    const long double y1 = eval(x);
    const long double y2 = s.eval(x);
    if (y1 != y2) return y1 < y2;
    return max(p, q) == max(s.p, s.q) ? min(p, q) < min(s.p, s.q)
                                      : max(p, q) < max(s.p, s.q);
  }

  bool contains(const Point& r) const {
    if (orientation(p, q, r) != 0) return false;
    return (q - p) * (r - p) >= 0 && (p - q) * (r - q) >= 0;
  }

 private:
  long double eval(const long double x) const {
    if (p.x == q.x) return (p.y + q.y) / 2.0;
    return (long double)(x - p.x) / (q.x - p.x) * (q.y - p.y) + p.y;
  }
};

bool edges_are_adjacent(const Segment& s, const Segment& r) {
  return s.p == r.p || s.p == r.q || s.q == r.p || s.q == r.q;
}

bool is_simple_aux(const vector<Point>& polygon) {
  const int N = polygon.size();

  const set<Point> unique_points{polygon.begin(), polygon.end()};
  if (polygon.size() != unique_points.size()) return false;

  for (int i = 0; i < N; i++) {
    const Segment edge1{polygon[i], polygon[(i + 1) % N]};
    const Segment edge2{polygon[(i + 1) % N], polygon[(i + 2) % N]};
    if (edge1.contains(polygon[(i + 2) % N])) return false;
    if (edge2.contains(polygon[i])) return false;
  }

  return true;
}

vector<tuple<Point, int, int>> sweep_line_events(const vector<Point>& polygon) {
  const int N = polygon.size();
  vector<tuple<Point, int, int>> events;

  for (int i = 0; i < N; i++) {
    const int prev_idx = (i - 1 + N) % N;
    const int next_idx = (i + 1) % N;

    events.emplace_back(polygon[i], prev_idx, next_idx);
  }

  sort(events.begin(), events.end());
  return events;
}

bool is_simple(const vector<Point>& polygon) {
  if (!is_simple_aux(polygon)) return false;

  set<Segment> active;

  const auto intersects_near_segments = [&](const Segment& e) -> bool {
    auto it = active.lower_bound(e);
    if (it != active.begin()) --it;

    for (int i = 0; i < 2 && it != active.end(); i++, it++)
      if (!edges_are_adjacent(*it, e) && it->intersects(e)) return true;

    return false;
  };

  for (const auto& [p, v1_idx, v2_idx] : sweep_line_events(polygon)) {
    const Segment edge1{p, polygon[v1_idx]};
    const Segment edge2{p, polygon[v2_idx]};

    if (intersects_near_segments(edge1) || intersects_near_segments(edge2)) return false;

    active.insert(edge1).second || active.erase(edge1);
    active.insert(edge2).second || active.erase(edge2);
  }

  assert(active.empty());

  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N && N) {
    assert(N >= 3);

    vector<Point> points(N);

    for (Point& p : points) cin >> p.x >> p.y;

    cout << (is_simple(points) ? "YES" : "NO") << endl;
  }
}
