#include <bits/stdc++.h>
using namespace std;

// TODO: Try using other input cases as well (e.g. the ones from Polygonal Puzzle
//       and Map Tiles)

struct Point {
  int x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  int cross(const Point& p) const { return x * p.y - y * p.x; }
  int operator*(const Point& p) const { return x * p.x + y * p.y; }
  bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const int cross = (a - o).cross(b - o);
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

 private:
  double eval(const double x) const {
    if (p.x == q.x) {
      // TODO: This also works. Why is it divided by 2 (in the next line)?
      return q.y;
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

bool edges_are_adjacent(const Segment& edge1, const Segment& edge2) {
  if (edge1.p == edge2.p || edge1.p == edge2.q) return true;
  if (edge1.q == edge2.p || edge1.q == edge2.q) return true;
  return false;
}

bool is_simple(const vector<Point>& polygon) {
  const int N = polygon.size();

  const set<Point> unique_points{polygon.begin(), polygon.end()};
  if (polygon.size() != unique_points.size()) return false;

  vector<tuple<Point, int, int>> events;

  for (int i = 0; i < N; i++) {
    const int prev_idx = (i - 1 + N) % N;
    const int next_idx = (i + 1) % N;

    events.emplace_back(polygon[i], prev_idx, next_idx);
  }

  sort(events.begin(), events.end());

  set<Segment> active;

  const auto intersects_near_segment = [&](const Segment& e) -> bool {
    const auto it = next(active.lower_bound(e));

    return it != active.end() && !edges_are_adjacent(*it, e) && it->intersects(e);
  };

  for (const auto& [p, v1_idx, v2_idx] : events) {
    const Segment edge1{p, polygon[v1_idx]};
    const Segment edge2{p, polygon[v2_idx]};

    // TODO: No need to delete segments??
    //       Maybe if I understand the comparator, I'll understand why this works.

    active.insert(edge1);
    active.insert(edge2);

    if (intersects_near_segment(edge1) || intersects_near_segment(edge2)) return false;
  }

  // TODO: This doesn't work. Should be the same...
  // assert(active.size() == N);

  return true;
}

int main() {
  // TODO: Test the segment intersection (fix the implementation).
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
