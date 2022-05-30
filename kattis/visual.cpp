#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: Refactor.

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point& p) const { return x * p.y - y * p.x; }
  ll operator*(const Point& p) const { return x * p.x + y * p.y; }
  bool operator<(const Point& p) const { return x == p.x ? y > p.y : x < p.x; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

short orientation(Point a, Point b, Point c) {
  const ll cross_value = (b - a).cross(c - a);
  return cross_value < 0 ? -1 : cross_value > 0;
}

struct Segment {
  const Point p, q;

  bool intersects(const Segment& s) const {
    if (contains(s.p) || contains(s.q)) return true;
    if (s.contains(p) || s.contains(q)) return true;
    bool o1 = orientation(p, q, s.p) != orientation(p, q, s.q);
    bool o2 = orientation(s.p, s.q, p) != orientation(s.p, s.q, q);
    return o1 && o2;
  }

 private:
  bool contains(const Point& r) const {
    return orientation(p, q, r) == 0 && (q - p) * (r - p) > 0 && (p - q) * (r - q) > 0;
  }
};

struct Rectangle {
  Rectangle(const Point& top_left, const Point& bottom_right)
      : top_left(top_left),
        bottom_right(bottom_right),
        p1(top_left),
        p2({top_left.x, bottom_right.y}),
        p3(bottom_right),
        p4({bottom_right.x, top_left.y}) {}

  bool edges_intersect(const Rectangle& r) const {
    for (const Segment& e1 : edges())
      for (const Segment& e2 : r.edges())
        if (e1.intersects(e2)) return true;

    return false;
  }

 private:
  const Point top_left, bottom_right, p1, p2, p3, p4;
  array<Segment, 4> edges() const {
    return {Segment{p1, p2}, {p2, p3}, {p3, p4}, {p4, p1}};
  }
};

int N, top_bottom[100001], bottom_top[100001];
vector<Point> top, bottom;
vector<tuple<Point, int, bool>> events;

bool sweep_line() {
  set<pair<int, int>> top_active;

  for (const auto& [p, idx, is_top] : events) {
    if (is_top) {
      const auto it = top_active.lower_bound({top[idx].y, -1});
      if (it != top_active.end() && it->first == p.y) return false;
      top_active.emplace(p.y, idx);
    } else {
      const auto it = top_active.lower_bound({p.y, -1});
      if (it == top_active.end()) return false;
      top_bottom[it->second] = idx;
      bottom_top[idx] = it->second;
      top_active.erase(it);
    }
  }

  top_active.clear();

  for (const auto& [_, idx, is_top] : events) {
    const int top_idx = is_top ? idx : bottom_top[idx];
    const Point& rect_top = top[top_idx];
    const Point& rect_bottom = bottom[top_bottom[top_idx]];

    const Rectangle rect{top[top_idx], bottom[top_bottom[top_idx]]};

    // why only from bottom? ;D no need to check above rect_top.y ?????
    // UPDATE: Actually both work, "rect_top.y + 1" or "rect_bottom.y + 1"
    // Note that I execute this for both the top and bottom events, but not sure
    // how that makes any difference.
    auto it = top_active.lower_bound({rect_bottom.y + 1, -1});
    if (it != top_active.end() && it->second != top_idx) {
      const Rectangle other_rectangle{top[it->second], bottom[top_bottom[it->second]]};
      if (rect.edges_intersect(other_rectangle)) return false;
    }

    // TODO: Why can this be in the middle as well, and it works properly???
    top_active.emplace(rect_top.y, top_idx).second ||
        top_active.erase({rect_top.y, top_idx});
  }

  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) {
    top.resize(N);
    bottom.resize(N);
    events.clear();

    for (Point& p : top) {
      cin >> p.y >> p.x;
      p.y = -p.y;
    }
    for (Point& p : bottom) {
      cin >> p.y >> p.x;
      p.y = -p.y;
    }

    for (int i = 0; i < N; i++) events.push_back({top[i], i, true});
    for (int i = 0; i < N; i++) events.push_back({bottom[i], i, false});
    sort(events.begin(), events.end());

    if (sweep_line()) {
      for (int i = 0; i < N; i++) cout << top_bottom[i] + 1 << endl;
    } else {
      cout << "syntax error" << endl;
    }
  }
}
