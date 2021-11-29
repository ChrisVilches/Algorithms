#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}
  ll operator^(const Point& p) const { return x * p.y - y * p.x; }
  ll operator*(const Point& p) const { return x * p.x + y * p.y; }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

bool inside(vector<Point>& polygon, Point& p) {
  for (int i = 0; i < (int)polygon.size() - 1; i++) {
    Point& a = polygon[i];
    Point& b = polygon[i + 1];

    ll cross = (b - a) ^ (p - a);

    // If they are collinear, and the vectors PA and PB are
    // 180 degrees, then the point is in the edge.
    // Also when one vector is 0, then the points (i.e. query point and vertex)
    // are in the same location, which also means inside.
    if (cross == 0) {
      if ((a - p) * (b - p) <= 0) return true;
    }

    if (cross <= 0) return false;
  }
  return true;
}

int main() {
  int N, Q;

  vector<Point> polygon;

  cin >> N >> Q;

  for (int i = 0; i < N; i++) {
    Point p;
    cin >> p.x >> p.y;
    polygon.push_back(p);
  }

  polygon.push_back(polygon[0]);

  while (Q--) {
    Point p;
    cin >> p.x >> p.y;
    cout << (inside(polygon, p) ? 'D' : 'F') << endl;
  }
}
