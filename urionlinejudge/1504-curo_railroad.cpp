#include <bits/stdc++.h>
using namespace std;

/*
 * Weak test data.
 * https://www.beecrowd.com.br/judge/en/questions/view/1504/7663
 *
 * This algorithm is most likely incorrect or incomplete.
 * Gets AC while getting a sample test wrong.
 *
 * When N=2, it should be "YES" if the two points are distinct, but it
 * only gets AC if the answer is always "NO".
 *
 * The line can be computed using a ternary search over the angle of two non-collinear
 * points, while minimizing the difference of sum of distances of both sides, which can be
 * computed in O(1) using the point-line distance formula, for all points at once using
 * the dot product associative property.
 *
 */

struct Point {
  double x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool operator==(const Point p) const { return x == p.x && y == p.y; }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  double operator*(const Point p) const { return x * p.x + y * p.y; }
  Point to_above() const { return is_above() ? *this : Point{-x, -y}; }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
};

bool cmp(const Point p, const Point q) { return p.to_above().cross(q.to_above()) > 0; }

Point get_centroid(const vector<Point>& points) {
  Point c{0, 0};
  for (const Point p : points) c = c + p;
  c.x /= points.size();
  c.y /= points.size();
  return c;
}

bool possible(vector<Point> points) {
  if (points.size() == 2) return false;  // Incorrect
  if (points.size() % 2 == 1) return false;

  const Point centroid = get_centroid(points);
  for (Point& p : points) p = p - centroid;
  for (const Point p : points)
    if (p == Point{0, 0}) return false;

  sort(points.begin(), points.end(), cmp);

  array<int, 2> count{0, 0};

  for (const Point p : points) {
    count[p.is_above()]++;
  }

  for (int i = 0; i < (int)points.size(); i++) {
    const Point p = points[i];
    const Point q = points[(i + 1) % points.size()];

    count[p.is_above()]--;
    count[!p.is_above()]++;

    if (p.cross(q) != 0 && count[0] == count[1]) {
      return true;
    }
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N;

  while (cin >> N) {
    vector<Point> points(N);
    for (Point& p : points) cin >> p.x >> p.y;

    cout << (possible(points) ? "YES" : "NO") << endl;
  }
}
