#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}

  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  int cross(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point& p) const { return cross(p) >= 0; }
};

int N;

vector<Point> points;

int memo[1000][1000];

int convex_hull(int p, int prev_idx) {
  if (memo[p][prev_idx] != -1) return memo[p][prev_idx];
  if (p == (int)points.size()) return 0;

  int ret = 0;

  Point& curr = points[p];
  Point& prev = points[prev_idx];

  for (int i = p + 1; i <= (int)points.size(); i++) {
    Point next = points[i % points.size()];

    Point prev_curr = curr - prev;
    Point curr_next = next - curr;
    Point next_origin = Point(0, 0) - next;

    int o1 = prev_curr.cross(curr_next);
    int o2 = curr_next.cross(next_origin);

    if (o1 >= 0 && o2 >= 0) {
      ret = max(ret, 1 + convex_hull(i, p));
    }
  }

  return memo[p][prev_idx] = ret;
}

void solve() {
  memset(memo, -1, sizeof memo);
  points.clear();

  while (N--) {
    Point p;
    cin >> p.x >> p.y;
    points.push_back(p);
  }

  sort(points.begin(), points.end());
  points.insert(points.begin(), Point(0, 0));

  int ans = 3;
  for (int i = 1; i < (int)points.size() - 2; i++)
    ans = max(ans, 1 + convex_hull(i, 0));

  cout << ans << endl;
}

int main() {
  int t = 1;
  while (scanf("%d", &N) == 1 && N > 0) {
    printf("Teste %d\n", t++);
    solve();
    printf("\n");
  }
}
