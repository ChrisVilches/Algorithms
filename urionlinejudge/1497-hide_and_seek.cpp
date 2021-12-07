#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point(ll x, ll y) : x(x), y(y) {}
  Point() {}

  inline int quad() const { return y != 0 ? (y > 0) : x > 0; }
  inline Point to(const Point& p) const { return p - *this; }

  bool operator<(const Point& p) const {
    return quad() != p.quad() ? quad() > p.quad() : (*this ^ p) > 0;
  }
  inline Point operator-(const Point& p) const {
    return Point(x - p.x, y - p.y);
  }
  inline ll operator^(const Point& p) const { return x * p.y - y * p.x; }
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}
  inline Segment operator-(const Point& o) const {
    return Segment(p - o, q - o);
  }

  inline bool intersects_positive_x_axis() const {
    if ((p ^ q) > 0) return q < p;
    return p < q;
  }
};

int S, K, W;
Point kids[10001];
Segment walls[10001];
set<int> curr_walls;

inline int sgn(ll x) { return (x > 0) - (x < 0); }

inline void toggle_segment(int segment_idx) {
  if (curr_walls.count(segment_idx))
    curr_walls.erase(segment_idx);
  else
    curr_walls.emplace(segment_idx);
}

bool kid_visible(const Point& center, const Point& kid) {
  for (auto it = curr_walls.begin(); it != curr_walls.end(); it++) {
    Segment s = walls[*it] - center;

    ll cross1 = s.p ^ kid;
    ll cross2 = s.p.to(kid) ^ kid.to(s.q);
    if (sgn(cross1) == sgn(cross2)) return false;
  }

  return true;
}

int can_see_count(const Point& center, vector<pair<Point, int>>& events) {
  curr_walls.clear();
  int visible_kids = 0;

  for (auto& ev : events) {
    auto [_, segment_idx] = ev;

    if (~segment_idx) {
      Segment s = walls[segment_idx] - center;
      if (s.intersects_positive_x_axis()) curr_walls.insert(segment_idx);
    }
  }

  for (auto& ev : events) {
    auto [p, segment_idx] = ev;

    if (~segment_idx)
      toggle_segment(segment_idx);
    else if (kid_visible(center, p))
      visible_kids++;
  }

  return visible_kids;
}

void solve() {
  for (int i = 0; i < K; i++) scanf("%lld %lld", &kids[i].x, &kids[i].y);

  for (int i = 0; i < W; i++)
    scanf("%lld %lld %lld %lld", &walls[i].p.x, &walls[i].p.y, &walls[i].q.x,
          &walls[i].q.y);

  for (int i = 0; i < S; i++) {
    const Point& seeker = kids[i];
    vector<pair<Point, int>> events;

    for (int j = 0; j < K; j++) {
      if (i == j) continue;
      Point kid = kids[j] - seeker;
      events.push_back(make_pair(kid, -1));
    }

    for (int j = 0; j < W; j++) {
      events.push_back(make_pair(walls[j].p - seeker, j));
      events.push_back(make_pair(walls[j].q - seeker, j));
    }

    sort(events.begin(), events.end());
    printf("%d\n", can_see_count(seeker, events));
  }
}

int main() {
  while (scanf("%d %d %d", &S, &K, &W) == 3) solve();
}
