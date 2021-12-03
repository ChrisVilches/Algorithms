#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}

  bool operator<(Point p) {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }
};

int cross(Point& O, Point& A, Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point>& A) {
  int n = A.size(), k = 0;
  if (n <= 3) return A;
  vector<Point> ans(2 * n);
  sort(A.begin(), A.end());
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross(ans[k - 2], ans[k - 1], A[i]) <= 0) k--;
    ans[k++] = A[i];
  }
  for (int i = n - 1, t = k + 1; i > 0; --i) {
    while (k >= t && cross(ans[k - 2], ans[k - 1], A[i - 1]) <= 0) k--;
    ans[k++] = A[i - 1];
  }
  ans.resize(k - 1);
  return ans;
}

int main() {
  vector<Point> terrain_a;
  vector<Point> terrain_b;

  for (int i = 0; i < 4; i++) {
    int x, y;
    cin >> x >> y;
    terrain_a.push_back(Point(x, y));
  }

  for (int i = 0; i < 4; i++) {
    int x, y;
    cin >> x >> y;
    terrain_b.push_back(Point(x, y));
  }

  vector<Point> hull_a = convex_hull(terrain_a);
  vector<Point> hull_b = convex_hull(terrain_b);

  long double area_a = 0;
  long double area_b = 0;

  for (int i = 2; i < (int)hull_a.size(); i++)
    area_a += fabs(cross(hull_a[0], hull_a[i - 1], hull_a[i])) / 2L;

  for (int i = 2; i < (int)hull_b.size(); i++)
    area_b += fabs(cross(hull_b[0], hull_b[i - 1], hull_b[i])) / 2L;

  if (area_b >= area_a)
    cout << "terreno B" << endl;
  else
    cout << "terreno A" << endl;
}
