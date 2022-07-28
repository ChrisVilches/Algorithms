#include <bits/stdc++.h>
using namespace std;
//#define BEECROWD_ONLINE_JUDGE

#ifdef BEECROWD_ONLINE_JUDGE
typedef long double d;
const d EPS = 1e-12;
#else
typedef double d;
const d EPS = 1e-6;
#endif

bool equal(const d a, const d b) { return fabs(a - b) < EPS; }

struct Point {
  d x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  bool operator==(const Point& p) const { return equal(x, p.x) && equal(y, p.y); }
  d operator*(const Point& p) const { return x * p.x + y * p.y; }
  d cross(const Point& p) const { return x * p.y - y * p.x; }
  Point scale(const d f) const { return {x * f, y * f}; }
  Point rot_ccw() const { return {-y, x}; }
  d magnitude() const { return hypot(x, y); }
  Point normalize() const { return {x / magnitude(), y / magnitude()}; }
  d dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const d cross = (a - o).cross(b - o);
  if (equal(cross, 0)) return 0;
  return cross > 0 ? 1 : -1;
}

struct Segment {
  Point p, q;

  static Segment horizontal_line(const d y) { return {{-1e6, y}, {1e6, y}}; }
  static Segment vertical_line(const d x) { return {{x, -1e6}, {x, 1e6}}; }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    return intersect(s) ? make_pair(true, intersection_point(s))
                        : make_pair(false, Point{});
  }

  Segment scale(const d f) const { return {p, p + (q - p).scale(f)}; }

  bool intersect(const Segment& s) const {
    const short o1 = orientation(p, q, s.p) * orientation(p, q, s.q) < 0;
    const short o2 = orientation(s.p, s.q, p) * orientation(s.p, s.q, q) < 0;
    return o1 && o2;
  }

 private:
  Point intersection_point(const Segment& s) const {
    const d factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

#define TILE_N 11
d tile_x, tile_y;
bool tiles[TILE_N][TILE_N];

int tiles_count() {
  int res = 0;
  for (int i = 0; i < TILE_N; i++)
    for (int j = 0; j < TILE_N; j++) res += tiles[i][j];

  return res;
}

bool is_ccw(const vector<Point>& polygon) {
  d total = 0;

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
  const d factor = 20;

  auto add = [&](Point p) {
    if (p.x < 0 || p.y < 0 || p.x > 6 * tile_x || p.y > 6 * tile_y) return;
    p.x = fmod(p.x, tile_x);
    p.y = fmod(p.y, tile_y);

    const int x1 = p.x * factor;
    const int y1 = p.y * factor;
    const int x2 = (tile_x - p.x) * factor;
    const int y2 = (tile_y - p.y) * factor;
    if (exist.count({x1, y1}) || exist.count({x2, y2})) return;

    offsets.push_back(p);
    offsets.push_back({tile_x - p.x, tile_y - p.y});

    exist.emplace(x1, y1);
    exist.emplace(x2, y2);
  };

  for (auto [x, y] : polygon) {
    add({x, 0});
    add({0, y});
    for (auto [_, y2] : polygon) add({x, y2});
  }

  for (int v = 0; v < (int)polygon.size(); v++) {
    const Point vertex = polygon[v];
    const Point vertex2 = polygon[(v + 1) % polygon.size()];
    const Point unit_dir = (vertex2 - vertex).normalize();

    for (int i = 0; i < TILE_N / 2; i++) {
      for (int j = 0; j < TILE_N / 2; j++) {
        const Point t{i * tile_x, j * tile_y};

        for (int w = 0; w < (int)polygon.size(); w++) {
          Segment edge{polygon[w] - vertex, polygon[(w + 1) % polygon.size()] - vertex};
          const Segment ray{t, t + unit_dir.scale(1e7)};
          const auto [intersect, point] = ray.intersect_non_collinear(edge);
          if (intersect) add(vertex + point - t);
        }
      }
    }

    for (int w = 0; w < (int)polygon.size(); w++) {
      const Point vert = polygon[w] - vertex;
      const Segment line{vert - unit_dir.scale(1e7), vert + unit_dir.scale(1e7)};

      for (int i = 0; i < TILE_N / 2; i++) {
        const auto [intersect1, point1] =
            line.intersect_non_collinear({{i * tile_x, -1e7}, {i * tile_x, 1e7}});
        if (intersect1) add(vertex + point1 - vert);

        const auto [intersect2, point2] =
            line.intersect_non_collinear({{-1e7, i * tile_y}, {1e7, i * tile_y}});
        if (intersect2) add(vertex + point2 - vert);
      }
    }
  }

  return offsets;
}

d angle(const Point& a, const Point& b) {
  const d x = atan2(a.cross(b), a * b);
  return x < 0 ? x + 2 * M_PI : x;
}

d angle(const Point& o, const Point& a, const Point& b) { return angle(a - o, b - o); }

bool vertex_intersection(const vector<Point>& polygon, Segment s, const int i) {
  const Point v1 = polygon[i];
  if (orientation(s.p, s.q, v1) != 0 || (s.q - s.p) * (v1 - s.p) < 0) return false;

  const Point v0 = i == 0 ? polygon.back() : polygon[i - 1];
  const Point v2 = polygon[(i + 1) % polygon.size()];

  const d edges_ang = angle(v1, v0, v2);
  d p_ang = angle(v1, v0, s.p);
  d q_ang = angle(v1, v0, s.q);

  if (p_ang > q_ang) swap(p_ang, q_ang), swap(s.p, s.q);

  return orientation(v0, v1, s.p) == 0 ? q_ang < edges_ang : p_ang < edges_ang;
}

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  const Segment ray1{p, {1e4, 1e4}};
  const Segment ray2{p, {1e4, 1e4 + 1e-5}};

  int intersections1 = 0;
  int intersections2 = 0;

  for (int i = 0; i < (int)polygon.size(); i++) {
    const Segment edge{polygon[i], polygon[(i + 1) % polygon.size()]};

    intersections1 += edge.intersect(ray1) || vertex_intersection(polygon, ray1, i);
    intersections2 += edge.intersect(ray2) || vertex_intersection(polygon, ray2, i);
  }

  return intersections1 % 2 == 1 && intersections2 % 2 == 1;
}

pair<int, int> get_tile(const Point& p) { return {p.x / tile_x, p.y / tile_y}; }

void mark_edge(const Point& p, const Point& q) {
  const Point unit_dir = (q - p).normalize();

  const Point mid_point = Segment{p, q}.scale(0.5).q + unit_dir.rot_ccw().scale(1e-6);
  const auto [i, j] = get_tile(mid_point);

  tiles[i][j] = true;
}

int dir(const d a, const d b, const d tile_size) {
  if (a > b) return equal(fmod(a, tile_size), 0) ? -1 : 0;
  return 1;
}

void mark_polygon_boundary(const vector<Point>& polygon) {
  for (int v = 0; v < (int)polygon.size(); v++) {
    Point p = polygon[v];
    const Point q = polygon[(v + 1) % polygon.size()];

    for (int it = 0; it < 18; it++) {
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
