#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point(ll x, ll y) : x(x), y(y) {}
  Point() {}

  inline Point reflection() const { return Point(-x, -y); }
  inline Point operator-(const Point& p) const {
    return Point(x - p.x, y - p.y);
  }
  inline ll operator^(const Point& p) const { return x * p.y - y * p.x; }
};

struct Segment {
  Point p, q;
  ll width() const { return abs(p.x - q.x); }
};

int N;
Segment segments[2001];
bool active[2001];

bool cmp(const tuple<Point, int, int>& a, const tuple<Point, int, int>& b) {
  Point p = get<0>(a);
  Point q = get<0>(b);
  if (p.y < 0) p = p.reflection();
  if (q.y < 0) q = q.reflection();
  return (p ^ q) > 0;
}

ll maximum_amount(Point& center) {
  vector<tuple<Point, int, int>> events;

  for (int i = 0; i < N; i++) {
    if (segments[i].p.y == center.y) continue;
    events.push_back({segments[i].p - center, segments[i].width(), i});
    events.push_back({segments[i].q - center, segments[i].width(), i});
  }

  sort(events.begin(), events.end(), cmp);

  ll ans = 0;
  ll curr = 0;

  ll subtract = 0;

  for (int i = 0; i < (int)events.size(); i++) {
    auto [p, width, segment_idx] = events[i];
    Point& next_point = get<0>(events[(i + 1) % events.size()]);

    if (active[segment_idx])
      subtract += width;
    else {
      curr += width;
      ans = max(ans, curr);
    }

    active[segment_idx] = !active[segment_idx];

    if ((p ^ next_point) == 0) continue;

    curr -= subtract;
    subtract = 0;
  }

  return ans;
}

int main() {
  while (scanf("%d", &N) == 1) {
    for (int i = 0; i < N; i++) {
      ll x1, x2, y;
      scanf("%lld %lld %lld", &x1, &x2, &y);
      segments[i] = {Point(x1, y), Point(x2, y)};
    }

    ll ans = 0;

    for (int i = 0; i < N; i++) {
      Segment& s = segments[i];
      ans = max(ans, s.width() + maximum_amount(s.p));
      ans = max(ans, s.width() + maximum_amount(s.q));
    }

    printf("%lld\n", ans);
  }
}
