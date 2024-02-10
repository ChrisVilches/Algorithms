#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
};

bool cmp_x(const Point p, const Point q) { return p.x < q.x; }
bool cmp_y(const Point p, const Point q) { return p.y < q.y; }

double brute_force(const span<Point>& points) {
  double res = DBL_MAX;

  for (int i = 0; i < (int)points.size(); i++) {
    for (int j = i + 1; j < (int)points.size(); j++) {
      res = min(res, points[i].dist(points[j]));
    }
  }

  return res;
}

double strip_closest(const span<Point>& strip, const double d) {
  double res = d;
  const int n = strip.size();

  sort(strip.begin(), strip.end(), cmp_y);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n && (strip[j].y - strip[i].y) < d; j++) {
      res = min(res, strip[i].dist(strip[j]));
    }
  }

  return res;
}

double closest_aux(const span<Point>& points) {
  if (points.size() <= 3) return brute_force(points);

  const int n = points.size();

  const int mid = n / 2;
  const Point mid_point = points[mid];

  double dl = closest_aux(points.subspan(0, mid));
  double dr = closest_aux(points.subspan(mid));

  const double d = min(dl, dr);

  vector<Point> strip;

  for (const Point p : points | views::filter([&](const Point p) {
                         return fabs(p.x - mid_point.x) < d;
                       })) {
    strip.push_back(p);
  }

  return min(d, strip_closest(strip, d));
}

double closest(vector<Point> points) {
  sort(points.begin(), points.end(), cmp_x);
  return closest_aux(points);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  while (cin >> N && N) {
    vector<Point> points(N);
    for (auto& p : points) cin >> p.x >> p.y;

    const double dist = closest(points);

    if (dist >= 10000) {
      cout << "INFINITY" << endl;
    } else {
      cout << fixed << setprecision(4) << dist << endl;
    }
  }
}
