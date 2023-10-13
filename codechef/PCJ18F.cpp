#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;

  Point rot_ccw(const double t) const {
    return {x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
};

double calculate_min_perimeter(const vector<Point> points) {
  double min_x = 1e15, min_y = 1e15;
  double max_x = -1e15, max_y = -1e15;

  for (const Point p : points) {
    min_x = min(min_x, p.x);
    max_x = max(max_x, p.x);
    min_y = min(min_y, p.y);
    max_y = max(max_y, p.y);
  }

  const double x_side = max_x - min_x;
  const double y_side = max_y - min_y;
  return 2 * (x_side + y_side);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  double M;

  while (cin >> N >> M) {
    vector<Point> points(N);
    for (Point& p : points) {
      cin >> p.x >> p.y;
      p = p.rot_ccw(atan(-M));
    }
    cout << fixed << setprecision(12) << calculate_min_perimeter(points) << endl;
  }
}
