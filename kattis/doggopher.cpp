#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  Point() {}
  double dist(const Point& p) const {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  }
};

bool possible(Point& gopher, Point& dog, Point& hole) {
  return dog.dist(hole) >= gopher.dist(hole) * 2;
}

int main() {
  Point gopher;
  Point dog;
  vector<Point> holes;

  cin >> gopher.x >> gopher.y;
  cin >> dog.x >> dog.y;

  double hx, hy;

  while (scanf("%lf %lf", &hx, &hy) == 2) holes.push_back(Point(hx, hy));

  for (Point& hole : holes) {
    if (possible(gopher, dog, hole)) {
      printf("The gopher can escape through the hole at (%.3f,%.3f).\n", hole.x,
             hole.y);
      return 0;
    }
  }

  cout << "The gopher cannot escape." << endl;
}
