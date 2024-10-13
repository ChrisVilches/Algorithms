#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  int x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  ll cross(const Point p) const { return (ll)x * p.y - (ll)y * p.x; }
  ll operator*(const Point p) const { return (ll)x * p.x + (ll)y * p.y; }
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
  bool operator<(const Point p) const { return y < p.y || (y == p.y && x < p.x); }
  double segment_dist(const Point p, const Point q) const {
    const Point r = *this;
    if ((q - p) * (r - p) <= 0) return p.dist(r);
    if ((p - q) * (r - q) <= 0) return q.dist(r);
    return fabs((q - p).cross(r - p)) / p.dist(q);
  }
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  const Point origin{0, 0};
  int n, m;

  while (cin >> n >> m) {
    vector<Point> P(n), Q(m);

    for (auto& p : P) cin >> p.x >> p.y;
    for (auto& p : Q) {
      cin >> p.x >> p.y;
      p.x = -p.x;
      p.y = -p.y;
    }

    const vector<Point> R = minkowski(P, Q);

    double dist = DBL_MAX;

    for (size_t i = R.size() - 1, j = 0; j < R.size(); i = j++) {
      dist = min(dist, origin.segment_dist(R[i], R[j]));
    }

    cout << fixed << setprecision(9) << max(dist - 60, 0.0) << endl;
  }
}
