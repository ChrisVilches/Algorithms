#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Weak test cases.
AC with inefficient solution.
Solution is most likely incorrect.
*/

struct Point {
  int x, y;
};

bool cmp_x(const Point& p, const Point& q) {
  return p.x < q.x || (p.x == q.x && p.y < q.y);
}

bool cmp_y(const Point& p, const Point& q) {
  return p.y < q.y || (p.y == q.y && p.x < q.x);
}

ll perimeter(vector<Point> points) {
  const int N = points.size();
  ll perimeter = 0;

  sort(points.begin(), points.end(), cmp_x);
  for (int i = 0; i < N; i += 2) {
    const Point& p1 = points[i];
    const Point& p2 = points[i + 1];
    perimeter += abs(p1.y - p2.y);
  }

  sort(points.begin(), points.end(), cmp_y);
  for (int i = 0; i < N; i += 2) {
    const Point& p1 = points[i];
    const Point& p2 = points[i + 1];
    perimeter += abs(p1.x - p2.x);
  }

  return perimeter;
}

ll area_inefficient(vector<Point> points) {
  const int N = points.size();
  ll area = 0;

  sort(points.begin(), points.end(), cmp_x);

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

    if (points.size() % 2 == 1) {
      cout << "impossible" << endl;
      continue;
    }

    cout << area_inefficient(points) << " " << perimeter(points) << endl;
  }
}
