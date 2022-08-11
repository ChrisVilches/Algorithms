#include <bits/stdc++.h>
using namespace std;
typedef pair<double, int> pdi;
typedef priority_queue<pdi, vector<pdi>, greater<pdi>> pqueue;

const double EPS = 1e-6;

// TODO: Refactor. Simplify.

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  Point scale(const double f) const { return {x * f, y * f}; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point& p) const { return x != p.x || y != p.y; }
  double operator*(const Point& p) const { return x * p.x + y * p.y; }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const double cross = (a - o).cross(b - o);
  if (fabs(cross) < EPS) return 0;
  return cross < 0 ? -1 : 1;
}

struct Segment {
  Point p, q;
  bool operator!=(const Segment& s) const { return p != s.p || q != s.q; }
  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  pair<bool, Point> intersect_adhoc(const Segment& s) const {
    if (q == s.p) return {true, q};

    if (orientation(p, q, s.q) > 0) {
      if (contains(s.p)) return {true, s.p};
      if (s.contains(q)) return {true, q};
    }

    return {intersect(s), intersection_point(s)};
  }

  bool contains(const Point& r) const {
    if (orientation(p, q, r) != 0) return false;
    return (q - p) * (r - p) > 0 && (p - q) * (r - q) > 0;
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

vector<Segment> segments;
unordered_set<int> active;

bool compare(const Point& o, const Point& a, const Point& b) {
  const short slope = orientation(o, a, b);
  return slope > 0 || (slope == 0 && a.x < b.x);
}

tuple<bool, Point, Segment> next_intersection(const Segment& above) {
  Point closest_point{1e6, 1e6};
  Segment inter_seg = above;

  for (const int seg_idx : active) {
    const Segment& s = segments[seg_idx];

    const auto [intersect, point] = above.intersect_adhoc(s);

    if (!intersect) continue;

    if (closest_point == point) {
      if (compare(point, inter_seg.q, s.q)) inter_seg = s;
    } else if (point.x < closest_point.x - EPS) {
      inter_seg = s;
      closest_point = point;
    }
  }

  return {above != inter_seg, closest_point, {closest_point, inter_seg.q}};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N && N > 0) {
    segments.clear();
    active.clear();

    map<double, int> optimal_segment;

    for (int i = 0; i < N; i++) {
      double left, right, height;
      cin >> left >> right >> height;

      const Point l{left, 0};
      const Point m{(left + right) / 2, height};
      const Point r{right, 0};

      if (!optimal_segment.count(l.x)) {
        optimal_segment[l.x] = segments.size();
      } else {
        const auto [p, q] = segments[optimal_segment[l.x]];
        if (compare(p, q, m)) optimal_segment[l.x] = segments.size();
      }

      segments.push_back({l, m});
      segments.push_back({m, r});
    }

    pqueue enter_events, exit_events;

    for (int i = 0; i < (int)segments.size(); i++) {
      enter_events.emplace(segments[i].p.x, i);
      exit_events.emplace(segments[i].q.x, i);
    }

    vector<Point> profile;

    Segment above;

    // TODO: Why does it become an infinite loop when I change the order of things?
    while (!enter_events.empty()) {
      above = segments[optimal_segment[enter_events.top().first]];
      profile.push_back(above.p);

      while (true) {
        while (!enter_events.empty() && enter_events.top().first <= above.q.x) {
          active.insert(enter_events.top().second);
          enter_events.pop();
        }

        while (!exit_events.empty() && exit_events.top().first < above.p.x) {
          active.erase(exit_events.top().second);
          exit_events.pop();
        }

        const auto [intersection, point, segment] = next_intersection(above);
        if (!intersection) break;

        profile.push_back(point);
        above = segment;
      }

      profile.push_back(above.q);
    }

    cout << fixed << setprecision(2) << profile_area(profile) << '\n';
  }
}
