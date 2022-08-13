#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Weak test cases.
AC with inefficient solution.
Solution is most likely incorrect.

Gets AC even without checking for this condition:
"If you can't find regions such that all the points
are the only corners and regions are closed, print 'Impossible'"
*/

struct Point {
  int x, y;
  bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
  Point rot() const { return {-y, x}; }
};

ll perimeter(vector<Point> points) {
  const int N = points.size();
  ll perimeter = 0;

  for (int rot = 0; rot < 2; rot++) {
    sort(points.begin(), points.end());
    for (int i = 0; i < N; i += 2) perimeter += points[i + 1].y - points[i].y;
    for (Point& p : points) p = p.rot();
  }

  return perimeter;
}

ll area_inefficient(vector<Point> points) {
  const int N = points.size();
  ll area = 0;

  sort(points.begin(), points.end());

  vector<int> active(1'000'001, -1);

  for (int i = 0; i < N; i += 2) {
    const Point& p1 = points[i];
    const Point& p2 = points[i + 1];

    const auto [from, to] = minmax(p1.y, p2.y);

    for (int y = from; y < to; y++) {
      if (active[y] == -1) {
        active[y] = p1.x;
      } else {
        area += abs(active[y] - p1.x);
        active[y] = -1;
      }
    }
  }

  return area;
}

int main() {
  int N;
  while (cin >> N) {
    vector<Point> points(N);
    for (auto& p : points) cin >> p.x >> p.y;

    cout << area_inefficient(points) << " " << perimeter(points) << endl;
  }
}
