#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y, color;
  Point operator-(const Point p) const { return {x - p.x, y - p.y, color}; }
  int cross(const Point p) const { return x * p.y - y * p.x; }
  int half() const { return !(y > 0 || (y == 0 && x > 0)); }
  Point to_first_half() const {
    if (half() == 0) return *this;
    return {-x, -y, color};
  }
};

bool cmp(const Point p, const Point q) {
  return p.to_first_half().cross(q.to_first_half()) > 0;
}

bool possible_aux(const vector<Point>& points) {
  int counts[2][2] = {{0, 0}, {0, 0}};
  int total_set = 0;

  for (const Point p : points) {
    if (p.color == 0) total_set++;
    counts[p.half()][p.color]++;
  }

  const auto ok = [&]() -> bool {
    return (counts[0][0] == total_set && counts[0][1] == 0) ||
           (counts[1][0] == total_set && counts[1][1] == 0);
  };

  if (ok()) return true;

  for (int i = 0; i < (int)points.size(); i++) {
    const Point p = points[i];
    const Point q = points[(i + 1) % points.size()];

    counts[!p.half()][p.color]++;
    counts[p.half()][p.color]--;

    if (p.cross(q) != 0 && ok()) return true;
  }

  return false;
}

bool possible(vector<Point> points) {
  for (int i = 0; i < (int)points.size(); i++) {
    vector<Point> centered;
    for (int j = 0; j < (int)points.size(); j++) {
      if (i == j) continue;
      centered.push_back(points[j] - points[i]);
    }
    sort(centered.begin(), centered.end(), cmp);
    if (possible_aux(centered)) return true;
  }

  return false;
}

int main() {
  int n, m;

  while (cin >> n >> m && n && m) {
    vector<Point> points(n + m);
    for (int i = 0; i < n + m; i++) {
      auto& p = points[i];
      cin >> p.x >> p.y;
      p.color = i < n;
    }

    cout << (possible(points) ? "YES" : "NO") << endl;
  }
}
