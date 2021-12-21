#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  inline int operator^(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point& p) const {
    return quad() != p.quad() ? quad() > p.quad() : (*this ^ p) > 0;
  }
  inline int quad() const { return y != 0 ? (y > 0) : x > 0; }
} points[107];

struct ConvexHull {
  int start_idx, last_idx, covered;
  double area;
};

int B, N;
vector<vector<ConvexHull>> convex_hulls;
double memo[105][55][105];

double dp(int idx, int b, int covered) {
  if (b == 0 && covered == 0) return 0;
  if (b == 0 && covered != 0) return DBL_MAX;
  if (b != 0 && covered <= 0) return DBL_MAX;
  if (memo[idx][b][covered] > 0) return memo[idx][b][covered];

  double min_area = DBL_MAX;

  for (ConvexHull& c : convex_hulls[idx]) {
    double area = c.area + dp((c.last_idx + 1) % N, b - 1, covered - c.covered);
    min_area = min(min_area, area);
  }

  return memo[idx][b][covered] = min_area;
}

ConvexHull create_convex_hull(const int start_idx, const int last_idx) {
  int covered = 0;
  vector<Point> vertices;

  for (int i = start_idx;; i = (i + 1) % N) {
    if (vertices.size() < 2) {
      vertices.push_back(points[i]);
      covered++;
      if (i == last_idx) break;
      continue;
    }

    while (vertices.size() >= 2) {
      Point a = points[i] - *(next(vertices.rbegin()));
      Point b = points[i] - *vertices.rbegin();
      if ((a ^ b) > 0) break;
      vertices.pop_back();
    }

    vertices.push_back(points[i]);
    covered++;
    if (i == last_idx) break;
  }

  double area = 0;
  for (int i = 0; i < (int)vertices.size() - 1; i++)
    area += fabs(vertices[i] ^ vertices[i + 1]) / 2L;

  return {start_idx, last_idx, covered, area};
}

int main() {
  while (scanf("%d %d", &B, &N) == 2 && B && N) {
    N--;
    convex_hulls.assign(N, vector<ConvexHull>());
    memset(memo, 0, sizeof memo);

    int origin_x, origin_y;
    cin >> origin_x >> origin_y;

    for (int i = 0; i < N; i++) {
      cin >> points[i].x >> points[i].y;
      points[i].x -= origin_x;
      points[i].y -= origin_y;
    }

    sort(points, points + N);

    for (int i = 0; i < N; i++)
      for (int j = i + 1;; j++) {
        j %= N;
        if ((points[j] ^ (Point(0, 0) - points[i])) < 0) break;
        convex_hulls[i].push_back(create_convex_hull(i, j));
      }

    double min_area = DBL_MAX;

    for (int i = 0; i < N; i++) min_area = min(min_area, dp(i, B, N));

    printf("%.2f\n", min_area);
  }
}
