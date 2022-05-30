#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  bool operator<(const Point& p) const { return x == p.x ? y > p.y : x < p.x; }
};

struct Rectangle {
  Rectangle(const Point& top_left, const Point& bottom_right)
      : top_left(top_left),
        bottom_right(bottom_right),
        p1(top_left),
        p2({top_left.x, bottom_right.y}),
        p3(bottom_right),
        p4({bottom_right.x, top_left.y}) {}

  bool intersects(const Rectangle& r) const {
    if (contains_nested(r) || r.contains_nested(*this)) return false;

    const bool c1 = contains(r.p1) || contains(r.p2) || contains(r.p3) || contains(r.p4);
    const bool c2 = r.contains(p1) || r.contains(p2) || r.contains(p3) || r.contains(p4);
    return c1 || c2;
  }

 private:
  const Point top_left, bottom_right, p1, p2, p3, p4;

  bool contains_inside(const Point& p) const {
    return top_left.x < p.x && p.x < bottom_right.x && top_left.y > p.y &&
           p.y > bottom_right.y;
  }

  bool contains_nested(const Rectangle& r) const {
    return contains_inside(r.p1) && contains_inside(r.p2) && contains_inside(r.p3) &&
           contains_inside(r.p4);
  }

  bool contains(const Point& p) const {
    return top_left.x <= p.x && p.x <= bottom_right.x && top_left.y >= p.y &&
           p.y >= bottom_right.y;
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

  for (const auto& [_, idx, is_top] : events) {
    const int top_idx = is_top ? idx : bottom_top[idx];
    const Point& rect_top = top[top_idx];

    const Rectangle rect{rect_top, bottom[top_bottom[top_idx]]};

    auto it = top_active.lower_bound({rect_top.y + 1, -1});
    if (it != top_active.end()) {
      const Rectangle other_rectangle{top[it->second], bottom[top_bottom[it->second]]};
      if (rect.intersects(other_rectangle)) return false;
    }

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
