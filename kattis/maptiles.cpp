#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double operator*(const Point& p) const { return x * p.x + y * p.y; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  Point scale(const double f) const { return {x * f, y * f}; }
  Point rot_ccw() const { return {-y, x}; }
  double magnitude() const { return hypot(x, y); }
  Point normalize() const { return {x / magnitude(), y / magnitude()}; }
  double dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const double cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : cross > 0;
}

struct Segment {
  Point p, q;

  static Segment horizontal_line(const double y) { return {{-1e5, y}, {1e5, y}}; }
  static Segment vertical_line(const double x) { return {{x, -1e5}, {x, 1e5}}; }
  Segment operator-(const Point& r) const { return {p - r, q - r}; }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    return intersect(s) ? make_pair(true, intersection_point(s))
                        : make_pair(false, Point{});
  }

  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  bool intersect(const Segment& s) const {
    return (orientation(p, q, s.p) * orientation(p, q, s.q) < 0) &&
           (orientation(s.p, s.q, p) * orientation(s.p, s.q, q) < 0);
  }

 private:
  Point intersection_point(const Segment& s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

#define TILE_N 11
double tile_x, tile_y;
bool tiles[TILE_N][TILE_N];

int tiles_count() {
  int res = 0;
  for (int i = 0; i < TILE_N; i++)
    for (int j = 0; j < TILE_N; j++) res += tiles[i][j];

  return res;
}

bool is_ccw(const vector<Point>& polygon) {
  double total = 0;

  for (int i = 0; i < (int)polygon.size(); i++) {
    const Point& p = polygon[i];
    const Point& q = polygon[(i + 1) % polygon.size()];
    total += (q.x - p.x) * (q.y + p.y);
  }

  return total < 0;
}

vector<Point> generate_offsets(const vector<Point>& polygon) {
  vector<Point> offsets;

  set<pair<int, int>> exist;
  const double factor = 10;

  auto add = [&](Point p) {
    p.x = fmod(p.x + TILE_N * tile_x, tile_x);
    p.y = fmod(p.y + TILE_N * tile_y, tile_y);

    const pair<int, int> added{floor(p.x * factor), floor(p.y * factor)};
    if (exist.count(added)) return;

    offsets.push_back({p.x, p.y});
    exist.insert(added);
  };

  vector<Point> tile_points;
  vector<Segment> grid_lines, polygon_edges;

  for (int i = -TILE_N; i < TILE_N; i++) {
    grid_lines.push_back(Segment::horizontal_line(i * tile_y));
    grid_lines.push_back(Segment::vertical_line(i * tile_x));
    for (int j = -TILE_N; j < TILE_N; j++)
      tile_points.push_back({i * tile_x, j * tile_y});
  }

  for (int i = 0; i < (int)polygon.size(); i++)
    polygon_edges.push_back({polygon[i], polygon[(i + 1) % polygon.size()]});

  for (const auto [x, _] : polygon)
    for (const auto [_, y] : polygon) add({tile_x - x, tile_y - y});

  for (const Segment& sliding_edge : polygon_edges) {
    const Point pivot_vertex = sliding_edge.p;
    const Point slide_dir = sliding_edge.q - sliding_edge.p;

    for (Segment edge : polygon_edges) {
      edge = edge - pivot_vertex;
      const Point& p = edge.p;

      for (const Point& t : tile_points) {
        const Segment ray{t, t + slide_dir};
        const auto [intersect, point] = ray.intersect_non_collinear(edge);
        if (intersect) add((t - point) - pivot_vertex);
      }

      for (const Segment& l : grid_lines) {
        const Segment ray{p, p - slide_dir};
        auto [intersect, point] = ray.intersect_non_collinear(l);
        if (intersect) add((point - p) - pivot_vertex);
      }
    }
  }

  return offsets;
}

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  const Segment ray{p, {1e4, 1e4 + 1e-5}};

  int intersections = 0;

  for (int i = 0; i < (int)polygon.size(); i++) {
    const Segment edge{polygon[i], polygon[(i + 1) % polygon.size()]};
    intersections += edge.intersect(ray);
  }

  return intersections % 2 == 1;
}

pair<int, int> get_tile(const Point& p) { return {p.x / tile_x, p.y / tile_y}; }

void mark_edge(const Point& p, const Point& q) {
  const Point unit_dir = (q - p).normalize();

  const Point mid_point = Segment{p, q}.scale(0.5).q + unit_dir.rot_ccw().scale(1e-6);
  const auto [i, j] = get_tile(mid_point);

  tiles[i][j] = true;
}

int dir(const double a, const double b, const double tile_size) {
  if (a > b) return fmod(a, tile_size) == 0 ? -1 : 0;
  return 1;
}

void mark_polygon_boundary(const vector<Point>& polygon) {
  for (int v = 0; v < (int)polygon.size(); v++) {
    Point p = polygon[v];
    const Point q = polygon[(v + 1) % polygon.size()];

    for (int it = 0; it < 2 * TILE_N; it++) {
      mark_edge(p, q);
      const auto [i, j] = get_tile(p);

      const Segment ver = Segment::vertical_line((i + dir(p.x, q.x, tile_x)) * tile_x);
      const Segment hor = Segment::horizontal_line((j + dir(p.y, q.y, tile_y)) * tile_y);

      auto [inter_v, point_ver] = ver.intersect_non_collinear({p, q});
      auto [inter_h, point_hor] = hor.intersect_non_collinear({p, q});

      if (!inter_v && !inter_h) break;

      if (!inter_v) point_ver = {-1e4, -1e4};
      if (!inter_h) point_hor = {-1e4, -1e4};

      const Point next_p = point_hor.dist(p) < point_ver.dist(p) ? point_hor : point_ver;
      mark_edge(p, next_p);
      p = next_p;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N;

  while (cin >> N >> tile_x >> tile_y) {
    vector<Point> polygon(N);

    Point min_point{DBL_MAX, DBL_MAX};

    for (Point& p : polygon) {
      cin >> p.x >> p.y;

      min_point.x = min(min_point.x, p.x);
      min_point.y = min(min_point.y, p.y);
    }

    for (Point& p : polygon) p = p - min_point;

    if (!is_ccw(polygon)) reverse(polygon.begin(), polygon.end());

    int ans = INT_MAX;

    for (const Point offset : generate_offsets(polygon)) {
      vector<Point> shifted_polygon = polygon;
      for (Point& p : shifted_polygon) p = p + offset;

      memset(tiles, 0, sizeof tiles);

      mark_polygon_boundary(shifted_polygon);

      for (int i = 0; i < TILE_N; i++) {
        for (int j = 0; j < TILE_N; j++) {
          if (tiles[i][j]) continue;
          const Point p{i * tile_x + 0.5, j * tile_y + 0.5};
          tiles[i][j] = point_inside_polygon(p, shifted_polygon);
        }
      }

      ans = min(ans, tiles_count());
    }

    cout << ans << endl;
  }
}
