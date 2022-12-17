#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  ll cross(const Point& p) const { return x * p.y - y * p.x; }
  ll operator*(const Point& p) const { return x * p.x + y * p.y; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
} points[1007];

short orientation(const Point o, const Point a, const Point b) {
  const ll cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : cross > 0;
}

bool acute_angle(const Point o, const Point a, const Point b) {
  return (a - o) * (b - o) > 0;
}

struct Segment {
  Point p, q;

  bool contains(const Point& r) const {
    return orientation(p, q, r) == 0 && acute_angle(p, q, r) && acute_angle(q, p, r);
  }

  bool intersects(const Segment& s) const {
    const bool o1 = orientation(p, q, s.p) * orientation(p, q, s.q) == -1;
    const bool o2 = orientation(s.p, s.q, p) * orientation(s.p, s.q, q) == -1;
    return o1 && o2;
  }
};

int N;

bool on(const Point& p) {
  for (int i = 0; i < N; i++) {
    if (points[i] == p) return true;

    const Segment edge{points[i], points[(i + 1) % N]};
    if (edge.contains(p)) return true;
  }

  return false;
}

bool in(const Point& p) {
  const Segment ray{p, {(int)1e8 + 50, (int)1e8 + 25}};

  int intersections = 0;

  for (int i = 0; i < N; i++) {
    const Segment edge{points[i], points[(i + 1) % N]};
    intersections += edge.intersects(ray);
  }

  return intersections % 2 == 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N && N) {
    for (int i = 0; i < N; i++) {
      cin >> points[i].x >> points[i].y;
    }

    int M;
    cin >> M;

    for (int i = 0; i < M; i++) {
      Point p;
      cin >> p.x >> p.y;

      if (on(p)) {
        cout << "on";
      } else {
        cout << (in(p) ? "in" : "out");
      }

      cout << '\n';
    }
  }
}
