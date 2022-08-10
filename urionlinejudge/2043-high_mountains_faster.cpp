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
  double dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const double cross = (a - o).cross(b - o);
  if (fabs(cross) < EPS) return 0;
  return cross < 0 ? -1 : 1;
}

struct Segment {
  Point p, q;

  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  pair<bool, Point> intersect_adhoc(const Segment& s) const {
    if (q == s.p) {
      return {true, s.p};
    }

    if (!(orientation(p, q, s.p) == 0 && orientation(p, q, s.q) == 0)) {
      if (contains(s.p) && orientation(p, q, s.q) > 0) {
        return {true, s.p};
      }

      if (s.contains(q) && orientation(s.p, s.q, p) > 0) {
        return {true, q};
      }
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

tuple<bool, Point, Segment> next_intersection(const Segment& above) {
  bool at_least_one_intersection = false;
  Point closest_point = above.q.scale(2);
  Segment inter_segment = above;

  for (const int seg_idx : active) {
    const Segment& s = segments[seg_idx];

    const auto [intersect, point] = above.intersect_adhoc(s);

    if (!intersect) continue;

    if (closest_point != point) {
      if (above.p.dist(closest_point) > above.p.dist(point)) {
        at_least_one_intersection = true;
        inter_segment = s;
        closest_point = point;
      }
    } else {
      const short slope = orientation(point, inter_segment.q, s.q);

      if (slope > 0 ||
          (slope == 0 && above.p.dist(inter_segment.q) <= above.p.dist(s.q))) {
        at_least_one_intersection = true;
        inter_segment = s;
      }
    }
  }

  if (!at_least_one_intersection) return {false, closest_point, inter_segment};

  return {true, closest_point, {closest_point, inter_segment.q}};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N && N > 0) {
    segments.clear();
    active.clear();

    for (int i = 0; i < N; i++) {
      double left, right, height;
      cin >> left >> right >> height;

      const Point l{left, 0};
      const Point m{(left + right) / 2, height};
      const Point r{right, 0};

      segments.push_back({l, m});
      segments.push_back({m, r});
    }

    pqueue enter_events, exit_events, right_events;

    double max_x = 0;

    for (int i = 0; i < (int)segments.size(); i++) {
      max_x = max(max_x, segments[i].q.x);

      enter_events.emplace(segments[i].p.x, i);
      exit_events.emplace(segments[i].q.x, i);

      right_events.emplace(segments[i].p.x, i);
    }

    vector<Point> profile;

    Segment above = segments[enter_events.top().second];

    profile.push_back(above.p);

    while (true) {
      while (!right_events.empty() && right_events.top().first <= above.q.x) {
        const Segment& s = segments[right_events.top().second];

        if (above.p == s.p) {
          const short slope = orientation(above.p, above.q, s.q);

          if (slope > 0 || (slope == 0 && above.q.x < s.q.x)) {
            profile.push_back(s.p);
            above = s;
          }
        }

        right_events.pop();
      }

      while (!enter_events.empty() && enter_events.top().first <= above.q.x) {
        const int seg_idx = enter_events.top().second;
        active.insert(seg_idx).second || active.erase(seg_idx);
        enter_events.pop();
      }

      while (!exit_events.empty() && exit_events.top().first < above.p.x) {
        const int seg_idx = exit_events.top().second;
        active.insert(seg_idx).second || active.erase(seg_idx);
        exit_events.pop();
      }

      const auto [intersection, point, segment] = next_intersection(above);
      if (intersection) {
        profile.push_back(point);
        above = segment;
        continue;
      }

      while (!right_events.empty() && right_events.top().first <= above.q.x)
        right_events.pop();

      if (above.q.x < right_events.top().first) {
        const Segment& s = segments[right_events.top().second];
        profile.push_back(above.q);
        profile.push_back(s.p);
        above = s;
      }

      if (above.q.x == max_x) {
        profile.push_back(above.q);
        break;
      }
    }

    cout << fixed << setprecision(2) << profile_area(profile) << endl;
  }
}
