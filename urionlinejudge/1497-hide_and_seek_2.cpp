#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
  ll x, y;

  inline Point to(const Point& p) const { return p - *this; }

  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
};

struct Segment {
  Point p, q;
  inline Segment operator-(const Point& o) const { return {p - o, q - o}; }
  inline bool intersects_positive_x_axis() const {
    const auto [a, b] = sorted_endpoints();
    return b < a;
  }

  pair<Point, Point> sorted_endpoints() const {
    return p.cross(q) > 0 ? make_pair(p, q) : make_pair(q, p);
  }

  bool operator<(const Segment& s) const {
    const auto [p1, q1] = sorted_endpoints();
    const auto [p2, q2] = s.sorted_endpoints();

    if (p1.cross(p2) > 0) {
      return p1.to(q1).cross(p1.to(p2)) < 0;
    } else {
      return p2.to(q2).cross(p2.to(p1)) > 0;
    }
  }
};

int S, K, W;
Point kids[10001];
Segment walls[10001];
set<Segment> curr_walls;

bool kid_visible(const Point& kid) {
  if (curr_walls.empty()) return true;

  const Segment& closest_wall = *curr_walls.begin();
  const auto [p, q] = closest_wall.sorted_endpoints();
  return p.to(q).cross(q.to(kid)) > 0;
}

int visible_count(const Point& center, vector<pair<Point, int>>& events) {
  curr_walls.clear();
  int ans = 0;

  for (const auto& [_, segment_idx] : events) {
    if (segment_idx == -1) continue;

    const Segment s = walls[segment_idx] - center;
    if (s.intersects_positive_x_axis()) curr_walls.insert(s);
  }

  for (const auto& [p, segment_idx] : events) {
    if (~segment_idx) {
      const Segment s = walls[segment_idx] - center;
      curr_walls.insert(s).second || curr_walls.erase(s);
    } else {
      ans += kid_visible(p);
    }
  }

  return ans;
}

void solve() {
  for (int i = 0; i < K; i++) cin >> kids[i].x >> kids[i].y;

  for (int i = 0; i < W; i++)
    cin >> walls[i].p.x >> walls[i].p.y >> walls[i].q.x >> walls[i].q.y;

  for (int i = 0; i < S; i++) {
    const Point& seeker = kids[i];
    vector<pair<Point, int>> events;

    for (int j = 0; j < K; j++) {
      if (i == j) continue;
      events.push_back({kids[j] - seeker, -1});
    }

    for (int j = 0; j < W; j++) {
      events.push_back({walls[j].p - seeker, j});
      events.push_back({walls[j].q - seeker, j});
    }

    sort(events.begin(), events.end());
    cout << visible_count(seeker, events) << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> S >> K >> W) solve();
}
