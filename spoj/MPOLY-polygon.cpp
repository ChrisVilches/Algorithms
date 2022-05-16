#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;

  Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  int cross(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point& p) const { return cross(p) > 0; }
};

int N, memo[101][101];

vector<Point> points;

int dp(int p, int prev_idx) {
  if (memo[p][prev_idx] != -1) return memo[p][prev_idx];

  int ret = 0;

  const Point& curr = points[p];
  const Point& prev = points[prev_idx];

  for (int i = p + 1; i < (int)points.size(); i++) {
    const Point& next = points[i];

    Point prev_curr = curr - prev;
    Point curr_next = next - curr;

    if (prev_curr.cross(curr_next) > 0) {
      ret = max(ret, 1 + dp(i, p));
    }
  }

  return memo[p][prev_idx] = ret;
}

void solve() {
  memset(memo, -1, sizeof memo);
  points = vector<Point>(N);

  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
  }

  sort(points.begin(), points.end());
  points.insert(points.begin(), Point{0, 0});

  int ans = 0;

  for (int i = 1; i < (int)points.size(); i++) {
    ans = max(ans, 1 + dp(i, 0));
  }

  cout << (1 + ans) << endl;
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) {
    solve();
    printf("\n");
  }
}
