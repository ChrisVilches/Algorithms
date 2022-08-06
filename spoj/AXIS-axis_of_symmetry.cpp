#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
  double x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double magnitude() const { return hypot(x, y); }
  void operator+=(const Point& p) {
    x += p.x;
    y += p.y;
  }

  bool is_slope_vertical() const { return fabs(x) < EPS; }

  double slope() const {
    if (is_slope_vertical()) return DBL_MAX;
    const double f = 100000;
    return round((y / x) * f) / f;
  }

  bool is_origin() const { return magnitude() < EPS; }

  Point mid_point(const Point& p) const { return {(x + p.x) / 2, (y + p.y) / 2}; }

  Point rot90() const { return {-y, x}; }

  bool same_magnitude(const Point& p) const {
    return fabs(magnitude() - p.magnitude()) < EPS;
  }
};

bool cmp(const Point& p, const Point& q) { return p.magnitude() < q.magnitude(); }

void add_all_slopes(const vector<Point>& points, map<double, int>& slope_freq) {
  for (int i = 0; i < (int)points.size(); i++) {
    for (int j = i + 1; j < (int)points.size(); j++) {
      const Point& p = points[i];
      const Point& q = points[j];

      Point line_point = p.mid_point(q);

      if (line_point.is_origin()) line_point = p.rot90();

      slope_freq[line_point.slope()] += 2;
    }
  }
}

bool possible(vector<Point>& points) {
  map<double, int> slope_freq;

  sort(points.begin(), points.end(), cmp);

  for (const Point& p : points) {
    slope_freq[p.slope()]++;
  }

  vector<vector<Point>> groups_by_distance;

  Point curr{0, 0};

  for (const Point& p : points) {
    if (!p.same_magnitude(curr)) {
      groups_by_distance.push_back({});
      curr = p;
    }

    groups_by_distance.back().push_back(p);
  }

  for (vector<Point>& group : groups_by_distance) {
    add_all_slopes(group, slope_freq);
  }

  for (const auto [_, freq] : slope_freq) {
    if (freq == (int)points.size()) return true;
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N && N > 0) {
    vector<Point> points(N);

    for (int i = 0; i < N; i++) {
      cin >> points[i].x >> points[i].y;
    }

    Point centroid{0, 0};

    for (const Point& p : points) {
      centroid += p;
    }

    centroid.x /= N;
    centroid.y /= N;

    vector<Point> centered_points;

    for (const Point& p : points) {
      const Point new_p = p - centroid;

      if (new_p.is_origin()) continue;

      centered_points.push_back(new_p);
    }

    cout << (possible(centered_points) ? "Y" : "N") << endl;
  }
}
