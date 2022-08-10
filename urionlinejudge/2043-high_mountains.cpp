#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

// TODO: Refactor

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  Point scale(const double f) const { return {x * f, y * f}; }
  bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const double cross = (a - o).cross(b - o);
  if (fabs(cross) < EPS) return 0;
  return cross < 0 ? -1 : 1;
}

struct Segment {
  Point p, q;

  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    return {intersect(s), intersection_point(s)};
  }

 private:
  bool intersect(const Segment& s) const {
    return (orientation(p, q, s.p) * orientation(p, q, s.q) < 0) &&
           (orientation(s.p, s.q, p) * orientation(s.p, s.q, q) < 0);
  }

  Point intersection_point(const Segment& s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

double profile_area(const vector<Point>& profile) {
  double res = 0;

  for (int i = 0; i < (int)profile.size() - 1; i++) {
    const Point& p = profile[i];
    const Point& q = profile[i + 1];

    const auto [min_height, max_height] = minmax(p.y, q.y);

    const double triangle_height = max_height - min_height;
    const double base = q.x - p.x;

    res += triangle_height * base / 2;
    res += base * min_height;
  }

  return res;
}

vector<pair<Point, int>> create_events(const vector<Segment>& segments) {
  vector<pair<Point, int>> events;

  for (int i = 0; i < (int)segments.size(); i++) {
    events.emplace_back(segments[i].p, i);
    events.emplace_back(segments[i].q, i);

    for (int j = i + 1; j < (int)segments.size(); j++) {
      const auto [intersect, point] = segments[i].intersect_non_collinear(segments[j]);

      if (intersect) {
        // TODO:
        // It's not needed to remove points below these segments, but it seems doing so
        // improves the runtime.
        events.emplace_back(point, i);
        events.emplace_back(point, j);
      }
    }
  }

  // TODO: Why does sorting by X still works? (gets slower though)
  sort(events.begin(), events.end(),
       [](const auto& a, const auto& b) { return get<0>(a).y < get<0>(b).y; });

  return events;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N && N > 0) {
    vector<Segment> segments;

    for (int i = 0; i < N; i++) {
      double left, right, height;
      cin >> left >> right >> height;

      const Point l{left, 0};
      const Point m{(left + right) / 2, height};
      const Point r{right, 0};

      segments.push_back({l, m});
      segments.push_back({m, r});
    }

    set<Point> active;

    for (const auto& [p, idx] : create_events(segments)) {
      const Segment& s = segments[idx];

      auto it = active.lower_bound({s.p.x, -1});
      while (it != active.end() && it->x < s.q.x) {
        const auto next_it = next(it);

        if (orientation(s.p, s.q, *it) < 0) active.erase(it);

        it = next_it;
      }

      active.insert(p);
    }

    const double area = profile_area(vector<Point>{active.begin(), active.end()});

    cout << fixed << setprecision(2) << area << endl;
  }
}
