#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}

  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  inline int operator^(const Point& p) const { return x * p.y - y * p.x; }
  Point to(const Point& p) const { return p - *this; }
};

vector<Point> points;

int N, Xa, Xb, memo[101];

int dp(int prev_idx) {
  if (~memo[prev_idx]) return memo[prev_idx];

  int ret = 0;
  for (int i = 0; i < N; i++) {
    if (i == prev_idx) continue;

    Point& prev = points[prev_idx];
    Point a(Xa, 0);
    Point b(Xb, 0);
    Point& next = points[i];

    if ((b.to(prev) ^ prev.to(next)) > 0 && (prev.to(a) ^ a.to(next)) > 0)
      ret = max(ret, dp(i));
  }

  return memo[prev_idx] = 1 + ret;
}

int main() {
  cin >> N >> Xa >> Xb;
  memset(memo, -1, sizeof memo);

  for (int i = 0; i < N; i++) {
    Point p;
    cin >> p.x >> p.y;
    points.push_back(p);
  }

  int ans = 0;

  for (int i = 0; i < N; i++) ans = max(ans, dp(i));

  cout << ans << endl;
}
