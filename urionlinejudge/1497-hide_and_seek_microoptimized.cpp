#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void print(uint32_t n) {
  if (n / 10) print(n / 10);
  putchar_unlocked(n % 10 + '0');
}

void fastscan(ll& x) {
  int neg = false;
  register int c;
  x = 0;
  c = getchar_unlocked();
  if (c == '-') {
    neg = true;
    c = getchar_unlocked();
  }
  for (; (c > 47 && c < 58); c = getchar_unlocked())
    x = 48 + (x << 1) + (x << 3) - c;
  if (!neg) x *= -1;
}

struct Point {
  ll x, y;
  int data;
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
    return (p.y * q.y <= 0) && p.x + (q.x - p.x) * p.y / (p.y - q.y) >= 0;
  }
};

int S, K, W;
Point kids[10001];
Segment walls[10001];
unordered_set<int> curr_walls;
Point events[10001 * 3];
int ev_n;

inline int sgn(ll x) { return (x > 0) - (x < 0); }

inline void toggle_segment(int segment_idx) {
  if (curr_walls.count(segment_idx))
    curr_walls.erase(segment_idx);
  else
    curr_walls.emplace(segment_idx);
}

bool kid_visible(const Point& center, const Point& kid) {
  ll cross1, cross2;
  for (auto it = curr_walls.begin(); it != curr_walls.end(); it++) {
    Segment s = walls[*it] - center;

    cross1 = s.p ^ kid;
    cross2 = s.p.to(kid) ^ kid.to(s.q);
    if (sgn(cross1) == sgn(cross2)) return false;
  }

  return true;
}

int can_see_count(const Point& center) {
  int visible_kids = 0;
  Point p;
  int segment_idx;
  curr_walls.clear();

  for (int i = 0; i < ev_n; i++) {
    segment_idx = events[i].data;

    if (~segment_idx) {
      Segment s = walls[segment_idx] - center;
      if (s.intersects_positive_x_axis()) curr_walls.insert(segment_idx);
    }
  }

  for (int i = 0; i < ev_n; i++) {
    p = events[i];
    segment_idx = p.data;

    if (~segment_idx)
      toggle_segment(segment_idx);
    else
      visible_kids += kid_visible(center, p);
  }

  return visible_kids;
}

void solve() {
  ll x, y;
  for (int i = 0; i < K; i++) {
    fastscan(x);
    fastscan(y);
    kids[i].x = x;
    kids[i].y = y;
  }

  for (int i = 0; i < W; i++) {
    fastscan(x);
    fastscan(y);
    walls[i].p.x = x;
    walls[i].p.y = y;

    fastscan(x);
    fastscan(y);
    walls[i].q.x = x;
    walls[i].q.y = y;
  }

  for (int i = 0; i < S; i++) {
    ev_n = 0;
    const Point& seeker = kids[i];

    for (int j = 0; j < K; j++) {
      if (i == j) continue;
      Point kid = kids[j] - seeker;
      kid.data = -1;
      events[ev_n++] = kid;
    }

    for (int j = 0; j < W; j++) {
      events[ev_n] = walls[j].p - seeker;
      events[ev_n++].data = j;

      events[ev_n] = walls[j].q - seeker;
      events[ev_n++].data = j;
    }

    sort(events, events + ev_n);
    print(can_see_count(seeker));
    putchar_unlocked('\n');
  }
}

int main() {
  while (scanf(" %d %d %d ", &S, &K, &W) == 3) solve();
}
