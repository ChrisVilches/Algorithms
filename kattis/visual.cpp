#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point& p) const { return x * p.y - y * p.x; }

  ll operator*(const Point& p) const { return x * p.x + y * p.y; }

  bool operator<(const Point& p) const {
    if (x == p.x) return y > p.y;
    return x < p.x;
  }

  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

short orientation(Point a, Point b, Point c) {
  ll cross_value = (b - a).cross(c - a);
  if (cross_value < 0) return -1;
  return cross_value > 0;
}

struct Segment {
  Point p, q;

  // TODO: Merge into one (and make private). No need for two different "contains"
  bool contains_except_endpoints(const Point& r) const {
    if (orientation(p, q, r) != 0) return false;
    return (q - p) * (r - p) > 0 && (p - q) * (r - q) > 0;
  }
  bool contains(const Point& r) const {
    return p == r || q == r || contains_except_endpoints(r);
  }

  bool intersects(const Segment& s) const {
    if (contains(s.p) || contains(s.q)) return true;
    if (s.contains(p) || s.contains(q)) return true;
    short o1 = orientation(p, q, s.p);
    short o2 = orientation(p, q, s.q);

    short o3 = orientation(s.p, s.q, p);
    short o4 = orientation(s.p, s.q, q);

    return o1 != o2 && o3 != o4;
  }
};

struct Rectangle {
  Point top_left, bottom_right;

  Point p1() const { return top_left; }
  Point p2() const { return {top_left.x, bottom_right.y}; }
  Point p3() const { return bottom_right; }
  Point p4() const { return {bottom_right.x, top_left.y}; }

  array<Segment, 4> all_edges() const {
    return {Segment{p1(), p2()}, {p2(), p3()}, {p3(), p4()}, {p4(), p1()}};
  }

  bool intersects(const Rectangle& r) const {
    for (const Segment& p : all_edges())
      for (const Segment& q : r.all_edges())
        if (p.intersects(q)) return true;

    return false;
  }
};

int N;
int ans[100001], ans_inv[100001];

void solve() {
  vector<Point> top(N), bottom(N);

  for (Point& p : top) {
    cin >> p.y >> p.x;
    p.y = -p.y;
  }
  for (Point& p : bottom) {
    cin >> p.y >> p.x;
    p.y = -p.y;
  }

  vector<tuple<Point, int, bool>> events;

  for (int i = 0; i < N; i++) events.push_back({top[i], i, true});
  for (int i = 0; i < N; i++) events.push_back({bottom[i], i, false});

  set<pair<int, int>> top_active;

  sort(events.begin(), events.end());

  for (const auto& [p, idx, is_top] : events) {
    if (is_top) {
      const auto it = top_active.lower_bound({top[idx].y, -1});
      if (it != top_active.end() && it->first == p.y) goto syntax_error;

      top_active.emplace(p.y, idx);

    } else {
      const auto it = top_active.lower_bound({p.y, -1});
      if (it == top_active.end()) goto syntax_error;
      ans[it->second] = idx;
      ans_inv[idx] = it->second;
      top_active.erase(it);
    }
  }

  top_active.clear();

  for (const auto& [p, idx, is_top] : events) {
    Point rectangle_top, rectangle_bottom;
    int top_idx, bottom_idx;

    if (is_top) {
      rectangle_top = top[idx];
      rectangle_bottom = bottom[ans[idx]];
      top_idx = idx;
      bottom_idx = ans[idx];
    } else {
      rectangle_top = top[ans_inv[idx]];
      rectangle_bottom = bottom[idx];
      top_idx = ans_inv[idx];
      bottom_idx = idx;
    }

    {
      auto it = top_active.lower_bound({rectangle_bottom.y + 1, -1});
      if (it != top_active.end() && it->second != top_idx) {
        Rectangle other_rectangle{top[it->second], bottom[ans[it->second]]};
        if (Rectangle{rectangle_top, rectangle_bottom}.intersects(other_rectangle)) {
          goto syntax_error;
        }
      }
    }

    {
      auto it = top_active.lower_bound({rectangle_top.y + 1, -1});
      if (it != top_active.end()) {
        Rectangle other_rectangle{top[it->second], bottom[ans[it->second]]};
        if (Rectangle{rectangle_top, rectangle_bottom}.intersects(other_rectangle)) {
          goto syntax_error;
        }
      }
    }

    if (is_top) {
      top_active.emplace(p.y, idx);
    } else {
      top_active.erase({rectangle_top.y, ans_inv[idx]});
    }
  }

  for (int i = 0; i < N; i++) {
    cout << ans[i] + 1 << endl;
  }

  return;

syntax_error:
  cout << "syntax error" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) solve();
}
