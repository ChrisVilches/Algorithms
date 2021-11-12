#include <bits/stdc++.h>

using namespace std;

int N, M;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
};

int sign(Point& p1, Point& p2, Point& p3) {
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool point_in_triangle(Point& pt, Point& v1, Point& v2, Point& v3) {
  int d1 = sign(pt, v1, v2);
  int d2 = sign(pt, v2, v3);
  int d3 = sign(pt, v3, v1);
  bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
  bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
  return !(has_neg && has_pos);
}

void solve() {
  vector<Point> white, black;

  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    black.push_back(Point(x, y));
  }

  for (int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;
    white.push_back(Point(x, y));
  }

  int ans = 0;

  for (int i = 0; i < (int)black.size(); i++)
    for (int j = i + 1; j < (int)black.size(); j++)
      for (int k = j + 1; k < (int)black.size(); k++) {
        int inside = 0;

        for (Point& w : white)
          if (point_in_triangle(w, black[i], black[j], black[k])) inside++;

        ans += pow(inside, 2);
      }

  cout << ans << endl;
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) solve();
}
