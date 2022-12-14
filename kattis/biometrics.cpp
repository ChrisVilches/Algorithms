#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

struct Point {
  double x, y;
  double dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
  void operator-=(const Point& p) {
    x -= p.x;
    y -= p.y;
  }
  bool operator==(const Point& p) const {
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }

  Point rot_ccw(const double t) const {
    return {x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
};

vector<vector<Point>> create_rotations(vector<Point> polygon) {
  vector<vector<Point>> polygons;
  const int n = polygon.size();
  for (int i = 0; i < n; i++) {
    const Point p = polygon[i];
    for (Point& point : polygon) point -= p;
    const Point q = polygon[(i + 1) % n];
    const double ang = atan2(q.y, -q.x);
    for (Point& point : polygon) point = point.rot_ccw(ang);
    polygons.push_back(polygon);
  }

  return polygons;
}

int main() {
  int N;

  while (cin >> N && N > 0) {
    vector<Point> polygon1(N), polygon2(N);
    for (int i = 0; i < N; i++) cin >> polygon1[i].x >> polygon1[i].y;
    for (int i = 0; i < N; i++) cin >> polygon2[i].x >> polygon2[i].y;

    const auto rotations1 = create_rotations(polygon1);
    auto rotations2 = create_rotations(polygon2);

    bool similar = false;

    for (const vector<Point>& rot1 : rotations1) {
      const double length1 = rot1[0].dist(rot1[1]);
      for (vector<Point>& rot2 : rotations2) {
        const double length2 = rot2[0].dist(rot2[1]);
        const double scale = length1 / length2;

        for (Point& v : rot2) {
          v.x *= scale;
          v.y *= scale;
        }

        if (rot1 == rot2) {
          similar = true;
        }
      }
    }

    cout << (similar ? "similar" : "dissimilar") << endl;
  }
}
