#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point scale(const ll f) const { return {x * f, y * f}; }
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  bool operator<(const Point p) const { return y < p.y || (y == p.y && x < p.x); }
};

vector<Point> minkowski(vector<Point> P, vector<Point> Q) {
  rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
  rotate(Q.begin(), min_element(Q.begin(), Q.end()), Q.end());

  const int n = P.size();
  const int m = Q.size();

  vector<Point> res;

  int i = 0, j = 0;

  while (i < n || j < m) {
    res.emplace_back(P[i % n] + Q[j % m]);
    const ll cross = (P[(i + 1) % n] - P[i % n]).cross(Q[(j + 1) % m] - Q[j % m]);
    i += cross >= 0;
    j += cross <= 0;
  }
  return res;
}

vector<Point> read_points() {
  int n;
  cin >> n;
  vector<Point> res(n);
  for (Point& p : res) cin >> p.x >> p.y;
  return res;
}

vector<Point> scale(vector<Point> polygon, const ll f) {
  for (Point& p : polygon) p = p.scale(f);
  return polygon;
}

short orientation(const Point o, const Point a, const Point b) {
  const ll x = (a - o).cross(b - o);
  return (x > 0) - (x < 0);
}

bool inside_triangle(const Point a, const Point b, const Point c, const Point p) {
  return orientation(a, b, p) >= 0 && orientation(b, c, p) >= 0 &&
         orientation(c, a, p) >= 0;
}

bool inside(const vector<Point>& polygon, const Point p) {
  const auto cmp = [&](const Point p, const Point q) {
    return orientation(polygon[0], p, q) == -1;
  };

  const auto it = lower_bound(polygon.rbegin() + 1, polygon.rend() - 1, p, cmp);
  return inside_triangle(polygon[0], *it, *prev(it), p);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  const vector<Point> P = read_points();
  const vector<Point> Q = read_points();
  const vector<Point> A = read_points();

  const vector<Point> m1 = minkowski(P, Q);
  const vector<Point> m2 = minkowski(scale(P, 2), scale(Q, -1));
  const vector<Point> m3 = minkowski(scale(P, -1), scale(Q, 2));

  for (const Point p : A) {
    const bool possible = inside(m1, p + p) || inside(m2, p) || inside(m3, p);
    cout << "NY"[possible];
  }

  cout << endl;
}
