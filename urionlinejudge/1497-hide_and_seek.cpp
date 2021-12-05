#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point(ll x, ll y) : x(x), y(y) {}
  Point() {}

  inline int quad() const { return y != 0 ? (y > 0) : x > 0; }
  Point to(const Point& p) const { return p - *this; }

  bool operator<(const Point& p) const {
    return quad() != p.quad() ? quad() > p.quad() : (*this ^ p) > 0;
  }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  inline ll operator^(const Point& p) const { return x * p.y - y * p.x; }
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}
  Segment operator-(const Point& o) const { return Segment(p - o, q - o); }

  int orientation(Point p, Point q, Point r) {
    ll val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
  }

  bool intersect(const Segment& s) {
    Point p1 = p;
    Point q1 = q;
    Point p2 = s.p;
    Point q2 = s.q;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    return (o1 != o2 && o3 != o4);
  }
};

int S, K, W;
const Segment positive_x_axis(Point(0, 0), Point(10000000L, 0));
Point kids[10001];
Segment walls[10001];
set<int> curr_walls;

inline void handle_segment(int segment_idx) {
  if (curr_walls.count(segment_idx))
    curr_walls.erase(segment_idx);
  else
    curr_walls.emplace(segment_idx);
}

bool kid_visible(const Point& center, const Point& kid) {
  for (auto it = curr_walls.begin(); it != curr_walls.end(); it++) {
    Segment s = walls[*it] - center;

    ll cross1 = s.p ^ (s.p.to(kid));
    ll cross2 = s.p.to(kid) ^ kid.to(s.q);

    if (cross1 > 0 && cross2 > 0) return false;
    if (cross1 < 0 && cross2 < 0) return false;
  }

  return true;
}

int can_see_count(const Point& center, vector<pair<Point, int>>& events) {
  curr_walls.clear();
  int visible_kids = 0;

  for (pair<Point, int>& ev : events) {
    auto [_, segment_idx] = ev;

    if (~segment_idx) {
      Segment s = walls[segment_idx] - center;
      if (s.intersect(positive_x_axis)) curr_walls.insert(segment_idx);
    }
  }

  for (pair<Point, int>& ev : events) {
    auto [p, segment_idx] = ev;

    if (~segment_idx)
      handle_segment(segment_idx);
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
