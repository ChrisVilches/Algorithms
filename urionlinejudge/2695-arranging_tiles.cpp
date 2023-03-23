#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  double cross(const Point p) const { return x * p.y - y * p.x; }
};

bool ccw(Point o, Point a, Point b) { return (a - o).cross(b - o) > 0; }

struct Tile {
  vector<Point> vertices;
  const int left_bottom = 0;
  const int right_bottom = 1;
  int left_upper, right_upper;
  double bottom_width, extra_left_width, extra_right_width;

  void set_upper_corners() {
    for (int i = 1; i < (int)vertices.size() - 1; i++)
      if (vertices[i].y == vertices[i + 1].y) {
        right_upper = i;
        left_upper = i + 1;
        break;
      }
  }

  void set_widths() {
    double min_x = DBL_MAX;
    double max_x = DBL_MIN;
    for (Point& v : vertices) {
      min_x = min(min_x, v.x);
      max_x = max(max_x, v.x);
    }

    extra_left_width = -min_x;
    extra_right_width = max_x - vertices[right_bottom].x;
    bottom_width = vertices[right_bottom].x;
  }

  bool intersect(const Tile& t, const double distance_from_right_bottom) const {
    const Point x{bottom_width + distance_from_right_bottom, 0};

    for (int i = right_bottom, j = t.vertices.size() - 1; i < right_upper; i++)
      for (; j >= t.left_upper && t.vertices[j].y <= vertices[i + 1].y; j--)
        if (ccw(vertices[i], vertices[i + 1], t.vertices[j] + x)) return true;

    for (int i = right_bottom, j = t.vertices.size() - 1; j > t.left_upper; j--)
      for (; i < right_upper && vertices[i].y <= t.vertices[j - 1].y; i++)
        if (!ccw(t.vertices[j] + x, t.vertices[j - 1] + x, vertices[i])) return true;

    return false;
  }

  double min_distance(const Tile& t) const {
    double lo = 0;
    double hi = extra_right_width + t.extra_left_width;
    for (int it = 0; it < 50; it++) {
      const double mid = (lo + hi) / 2;
      if (intersect(t, mid))
        lo = mid;
      else
        hi = mid;
    }
    return lo;
  }

  void read() {
    int k;
    cin >> k;
    vertices.resize(k);
    for (Point& p : vertices) cin >> p.x >> p.y;
    vertices.push_back(vertices[0]);
    set_upper_corners();
    set_widths();
  }
};

vector<Tile> tiles;
double dist[17][17];
double memo[1 << 15][15];
bool ok[1 << 15][15];

double dp(const int visited, const int curr_idx) {
  if (__builtin_popcount(visited) == tiles.size())
    return tiles[curr_idx].bottom_width + tiles[curr_idx].extra_right_width;

  if (ok[visited][curr_idx]) return memo[visited][curr_idx];

  double ret = DBL_MAX;

  for (int i = 0; i < (int)tiles.size(); i++) {
    if ((visited & (1 << i)) != 0) continue;

    const double width =
        tiles[curr_idx].bottom_width + dist[curr_idx][i] + dp(visited | (1 << i), i);

    ret = min(ret, width);
  }

  ok[visited][curr_idx] = true;
  return memo[visited][curr_idx] = ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    memset(ok, 0, sizeof ok);
    tiles.resize(N);
    for (Tile& t : tiles) t.read();

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        if (i != j) dist[i][j] = tiles[i].min_distance(tiles[j]);

    double ans = DBL_MAX;

    for (int i = 0; i < (int)tiles.size(); i++)
      ans = min(ans, tiles[i].extra_left_width + dp(1 << i, i));

    cout << fixed << setprecision(3) << ans << endl;
  }
}
