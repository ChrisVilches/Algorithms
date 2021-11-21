#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x, y;
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}

  int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return val < 0 ? -1 : val > 0;
  }

  bool intersect(const Segment& s) {
    Point p1 = p, p2 = s.p;
    Point q1 = q, q2 = s.q;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    return o1 != o2 && o3 != o4;
  }
};

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

    extra_left_width = vertices[left_bottom].x - min_x;
    extra_right_width = max_x - vertices[right_bottom].x;
    bottom_width = vertices[right_bottom].x;
  }

  inline Segment edge(int u, int v, double x_offset) {
    Segment s(vertices[u], vertices[v]);
    s.p.x += x_offset;
    s.q.x += x_offset;
    return s;
  }

  bool intersect(Tile& t, double distance_from_right_bottom) {
    double x_offset = vertices[right_bottom].x + distance_from_right_bottom;
    int j = t.vertices.size() - 1;
    for (int i = right_bottom; i < right_upper; i++) {
      for (; j > t.left_upper; j--) {
        Segment i_segment = edge(i, i + 1, 0);
        Segment j_segment = t.edge(j, j - 1, x_offset);
        if (i_segment.intersect(j_segment)) return true;
        if (t.vertices[j - 1].y > vertices[i + 1].y) break;
      }
    }
    return false;
  }

  double min_distance(Tile& t) {
    double left = 0;
    double right = extra_right_width + t.extra_left_width;
    while (right - left > 0.00001) {
      double mid = (right + left) / 2;
      if (intersect(t, mid))
        left = mid;
      else
        right = mid;
    }
    return left;
  }

  void read() {
    int k;
    scanf("%d", &k);
    while (k--) {
      Point p;
      scanf("%lf %lf", &p.x, &p.y);
      vertices.push_back(p);
    }
    vertices.push_back(vertices[0]);
    set_upper_corners();
    set_widths();
  }
};

int N;
vector<Tile> tiles;

double dist[17][17];
double memo[1 << 15][15];
bool ok[1 << 15][15];

double dp(int visited, int curr_idx) {
  if (__builtin_popcount(visited) == tiles.size())
    return tiles[curr_idx].bottom_width + tiles[curr_idx].extra_right_width;

  if (ok[visited][curr_idx]) return memo[visited][curr_idx];

  double ret = DBL_MAX;

  for (int i = 0; i < (int)tiles.size(); i++) {
    if ((visited & (1 << i)) != 0) continue;

    double width = tiles[curr_idx].bottom_width + dist[curr_idx][i] +
                   dp(visited | (1 << i), i);

    ret = min(ret, width);
  }

  ok[visited][curr_idx] = true;
  return memo[visited][curr_idx] = ret;
}

void solve() {
  tiles.clear();
  memset(memo, -10, sizeof memo);
  memset(ok, 0, sizeof ok);

  for (int i = 0; i < N; i++) {
    Tile t;
    t.read();
    tiles.push_back(t);
  }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (i != j) dist[i][j] = tiles[i].min_distance(tiles[j]);

  double ans = DBL_MAX;

  for (int i = 0; i < (int)tiles.size(); i++)
    ans = min(ans, tiles[i].extra_left_width + dp(1 << i, i));

  printf("%.3f\n", ans);
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
