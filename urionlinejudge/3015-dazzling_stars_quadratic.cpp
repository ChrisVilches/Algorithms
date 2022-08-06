#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y, b;
  int cross(const Point& p) const { return x * p.y - y * p.x; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y, b}; }
  bool operator<(const Point& p) const { return cross(p) > 0; }
};

bool possible(const vector<Point>& points) {
  vector<Point> directions;

  for (int i = 0; i < (int)points.size(); i++)
    for (int j = 0; j < (int)points.size(); j++)
      if (points[i].b < points[j].b) directions.push_back(points[j] - points[i]);

  if (directions.empty()) return true;

  Point a = directions.front();
  Point b = a;

  for (const Point& dir : directions) {
    if (a.cross(dir) != 0) {
      b = dir;
      break;
    }
  }

  if (b < a) swap(a, b);

  for (const Point& dir : directions) {
    if (dir < a && b < dir) return false;

    a = min(a, dir);
    b = max(b, dir);
  }

  return true;
}

int main() {
  int N;

  while (cin >> N) {
    vector<Point> points(N);

    for (Point& p : points) cin >> p.x >> p.y >> p.b;

    cout << (possible(points) ? "Y" : "N") << endl;
  }
}
