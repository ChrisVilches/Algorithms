#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

struct Point {
  ld x, y;
  inline Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  inline Point operator+(const Point& p) const { return Point{x + p.x, y + p.y}; }
  inline Point to(const Point& p) const { return p - *this; }
  ld operator*(const Point& p) const { return x * p.x + y * p.y; }
  inline ld magnitude() const { return sqrt((x * x) + (y * y)); }
  Point normalize() const { return Point{x / magnitude(), y / magnitude()}; }
  inline ld dist(const Point& p) { return to(p).magnitude(); }
  Point scale(ld f) const { return Point{x * f, y * f}; }
  bool operator<(const Point& p) const { return y == p.y ? x < p.x : y < p.y; }

  Point rot_ccw(ld t) const {
    return Point{x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
};

ld cross_product(Point O, Point& A, Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

ld cross_product(Point A, Point B) { return cross_product(Point{0, 0}, A, B); }

vector<Point> convex_hull(vector<Point>& A) {
  int n = A.size(), k = 0;
  if (n <= 3) return A;
  vector<Point> ans(2 * n);
  sort(A.begin(), A.end());
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross_product(ans[k - 2], ans[k - 1], A[i]) <= 0) k--;
    ans[k++] = A[i];
  }
  for (size_t i = n - 1, t = k + 1; i > 0; --i) {
    while (k >= t && cross_product(ans[k - 2], ans[k - 1], A[i - 1]) <= 0) k--;
    ans[k++] = A[i - 1];
  }
  ans.resize(k - 1);
  return ans;
}

int N;
ld EPS = 1e-10;
vector<Point> hull;

Point get_projection(const Point& o, const Point& p, const Point& q) {
  const Point a = o.to(p);
  const Point b = o.to(q);
  ld proj = (a * b) / a.magnitude();
  return o + a.normalize().scale(proj);
}

vector<Point> soften_polygon(const vector<Point>& polygon) {
  vector<Point> res;
  int n = (int)polygon.size();

  for (int i = 1; i <= n; i++) {
    const Point& a = polygon[i - 1];
    const Point& b = polygon[i % n];
    const Point& c = polygon[(i + 1) % n];

    bool should_soften = b.to(a) * b.to(c) >= 0;

    if (should_soften) res.push_back(a + a.to(b).rot_ccw(-EPS).scale(1 - EPS));
    res.push_back(b);
    if (should_soften) res.push_back(c + c.to(b).rot_ccw(EPS).scale(1 - EPS));
  }

  return res;
}

inline Point vertex_at(int i) { return hull[i % hull.size()]; }
inline Point edge_at(int i) { return vertex_at(i).to(vertex_at(i + 1)); }

pair<ld, ld> get_rectangle(int i, int j, int k, int l) {
  Point v1 = get_projection(vertex_at(i), vertex_at(i + 1), vertex_at(j));
  Point v2 = get_projection(v1, vertex_at(j), vertex_at(k));
  Point v3 = get_projection(v2, vertex_at(k), vertex_at(l));

  ld side1 = v1.dist(v2);
  ld side2 = v2.dist(v3);

  return {side1 * side2, (side1 + side2) * 2L};
}

void solve() {
  vector<Point> points(N);

  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
  }

  ld area = 1e15;
  ld perimeter = 1e15;

  hull = soften_polygon(convex_hull(points));

  for (int i = 0, j = 1, k = 2, l = 3; i < (int)hull.size(); i++) {
    Point edge = edge_at(i);

    while (edge * edge_at(j) > 0) j++;
    while (k <= j || cross_product(edge, edge_at(k)) > 0) k++;
    while (l <= k || edge * edge_at(l) < 0) l++;

    auto [new_area, new_perimeter] = get_rectangle(i, j, k, l);

    area = min(area, new_area);
    perimeter = min(perimeter, new_perimeter);
  }

  cout << setprecision(2) << fixed << area << ' ' << perimeter << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N && N > 0) solve();
}
