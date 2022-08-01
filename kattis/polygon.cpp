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

  // TODO: This implementation is weird.
  //       Just write some unit tests to check it all works correctly.
  bool intersects(const Segment& s) const {
    const short o1 = orientation(p, q, s.p);
    const short o2 = orientation(p, q, s.q);
    const short o3 = orientation(s.p, s.q, p);
    const short o4 = orientation(s.p, s.q, q);

    if (o1 * o2 == 0) return contains(s.p) || contains(s.q);
    if (o3 * o4 == 0) return s.contains(p) || s.contains(q);

    return (o1 * o2) < 0 && (o3 * o4) < 0;
  }

  // TODO: Understand this.
  bool operator<(const Segment& s) const {
    const int l = max(min(p.x, q.x), min(s.p.x, s.q.x));
    const int r = min(max(p.x, q.x), max(s.p.x, s.q.x));
    const double x = (l + r) / 2.0;
    const double y = eval(x);
    const double sy = s.eval(x);
    if (y != sy) return y < sy;
    if (max(p, q) == max(s.p, s.q)) return min(p, q) < min(s.p, s.q);
    return max(p, q) < max(s.p, s.q);
  }

  // private:
  double eval(const double x) const {
    if (p.x == q.x) {
      // TODO: This also works. Why is it divided by 2 (in the next line)?
      // return q.y;
      return (p.y + q.y) / 2.0;
    } else {
      return (double)(x - p.x) / (q.x - p.x) * (q.y - p.y) + p.y;
    }
  }

  bool contains(const Point& r) const {
    if (orientation(p, q, r) != 0) return false;
    return (q - p) * (r - p) >= 0 && (p - q) * (r - q) >= 0;
  }
};

bool edges_are_adjacent(const Segment& s, const Segment& r) {
  return s.p == r.p || s.p == r.q || s.q == r.p || s.q == r.q;
}

bool is_simple(const vector<Point>& polygon) {
  const int N = polygon.size();

  if (N < 3) return false;

  const set<Point> unique_points{polygon.begin(), polygon.end()};
  if (polygon.size() != unique_points.size()) return false;

  for (int i = 0; i < N; i++) {
    const Segment edge{polygon[i], polygon[(i + 1) % N]};
    if (edge.contains(polygon[(i + 2) % N])) return false;
  }

  vector<tuple<Point, int, int>> events;

  for (int i = 0; i < N; i++) {
    const int prev_idx = (i - 1 + N) % N;
    const int next_idx = (i + 1) % N;

    events.emplace_back(polygon[i], prev_idx, next_idx);
  }

  sort(events.begin(), events.end());

  set<Segment> active;

  const auto intersects_near_segments = [&](const Segment& e) -> bool {
    auto it = active.lower_bound(e);

    if (it != active.begin()) --it;

    // TODO: Is it possible to do just one iteration? (or two: segments above and below).
    //       Understand the comparator first.
    for (int i = 0; i < 3 && it != active.end(); i++, it++) {
      assert(it != active.end());
      if (!edges_are_adjacent(*it, e) && it->intersects(e)) return true;
    }

    return false;
  };

  // TODO: For now, use this for testing (it should ADD and REMOVE, i.e.
  //       size must change).
  const auto toggle = [&](const Segment& s) -> void {
    const int bef = active.size();

    if (active.count(s)) {
      active.erase(s);
      assert((int)active.size() == bef - 1);
    } else {
      active.insert(s);
      assert((int)active.size() == bef + 1);
    }
  };

  for (const auto& [p, v1_idx, v2_idx] : events) {
    const Segment edge1{p, polygon[v1_idx]};
    const Segment edge2{p, polygon[v2_idx]};

    if (intersects_near_segments(edge1) || intersects_near_segments(edge2)) return false;

    toggle(edge1);
    toggle(edge2);
    // active.insert(edge1).second || active.erase(edge1);
    // active.insert(edge2).second || active.erase(edge2);
  }

  assert(active.empty());

  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // TODO: Test the segment intersection (fix the implementation).
  // For now it works OK but maybe there are some cases that fail, and that's why
  // the sweep line doesn't work 100% fine.
  {
    Segment e1{{5, 5}, {10, 5}};
    Segment e2{{50, 5}, {100, 5}};
    assert(!e1.intersects(e2));
  }

  {
    Segment e1{{0, 0}, {0, 10}};
    Segment e2{{0, 5}, {10, 5}};
    assert(e1.intersects(e2));
  }

  int N;

  while (cin >> N && N) {
    vector<Point> points(N);

    for (Point& p : points) cin >> p.x >> p.y;

    cout << (is_simple(points) ? "YES" : "NO") << endl;
  }
}
