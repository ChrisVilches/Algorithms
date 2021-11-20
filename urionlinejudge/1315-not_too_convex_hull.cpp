#include <bits/stdc++.h>

using namespace std;
typedef long double ld;

int B, N;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}

  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  inline int operator^(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point& p) const {
    return quad() != p.quad() ? quad() > p.quad() : (*this ^ p) > 0;
  }
  Point to(const Point& p) const { return p - *this; }
  inline int quad() const { return y != 0 ? (y > 0) : x > 0; }
};

vector<Point> points;

struct ConvexHull {
  int start_idx;
  int last_idx;
  int covered;
  ld area;

  static optional<ConvexHull> try_create(int i, int j) {
    if ((points[j].to(Point(0, 0)) ^ Point(0, 0).to(points[i])) < 0)
      return nullopt;

    return ConvexHull(i, j);
  }

 private:
  ConvexHull(int i, int j) : start_idx(i), last_idx(j) { build(); }
  vector<Point> vertices;

  void compute_area() {
    area = 0;
    for (int i = 0; i < (int)vertices.size() - 1; i++)
      area += fabs(vertices[i] ^ vertices[i + 1]) / 2L;
  }

  void build() {
    covered = 0;

    for (int i = start_idx;; i = (i + 1) % points.size()) {
      if (vertices.size() < 2) {
        vertices.push_back(points[i]);
        covered++;
        if (i == last_idx) break;
        continue;
      }

      while (vertices.size() >= 2) {
        Point a = vertices[vertices.size() - 2].to(points[i]);
        Point b = vertices[vertices.size() - 1].to(points[i]);
        if ((a ^ b) > 0) break;
        vertices.pop_back();
      }

      vertices.push_back(points[i]);
      covered++;
      if (i == last_idx) break;
    }

    compute_area();
  }
};

vector<vector<ConvexHull>> convex_hulls;
ld memo[105][55][105];

ld dp(int idx, int b, int covered) {
  if (b == 0 && covered == 0) return 0;
  if (b == 0 && covered != 0) return DBL_MAX;
  if (b != 0 && covered <= 0) return DBL_MAX;
  if (memo[idx][b][covered] > -1) return memo[idx][b][covered];

  ld min_area = DBL_MAX;

  for (ConvexHull& c : convex_hulls[idx]) {
    ld area = c.area +
              dp((c.last_idx + 1) % points.size(), b - 1, covered - c.covered);
    min_area = min(min_area, area);
  }

  return memo[idx][b][covered] = min_area;
}

void solve() {
  points.clear();
  convex_hulls.clear();
  memset(memo, -1, sizeof memo);

  int origin_x, origin_y;
  cin >> origin_x >> origin_y;
  N--;
  while (N--) {
    Point p;
    cin >> p.x >> p.y;
    p.x -= origin_x;
    p.y -= origin_y;
    points.push_back(p);
  }

  sort(points.begin(), points.end());

  convex_hulls.assign(points.size(), vector<ConvexHull>());

  for (int i = 0; i < (int)points.size(); i++)
    for (int j = i + 1;; j++) {
      j %= (int)points.size();
      if (i == j) break;
      optional<ConvexHull> ch = ConvexHull::try_create(i, j);
      if (!ch.has_value()) break;
      convex_hulls[i].push_back(ch.value());
    }

  ld min_area = DBL_MAX;

  for (int i = 0; i < (int)points.size(); i++)
    min_area = min(min_area, dp(i, B, points.size()));

  printf("%.2Lf\n", min_area);
}

int main() {
  while (scanf("%d %d", &B, &N) == 2 && B && N) solve();
}
