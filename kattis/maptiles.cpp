#include <bits/stdc++.h>
using namespace std;

/*
TODO:
* Refactor
* Modify the "point inside polygon" code so that it works for any polygon. Use the
  "vertex/collinear intersection" found in kattis/airport that I made
* Modify the boundary marking so that it's fast (obtain the tiles from the line, instead
  of traversing all tiles)
* Make it faster.
* Remove the "intermediate points" thing.
* Make it less than 300 lines.
* Remove hardcoded strange numbers like 6* or /2, etc.
* Point in polygon doesn't work for any ray. Using {10000, 10000} doesn't work
  for one case where the ray intersects a very acute polygon vertex.

I think if I implement the "quick boundary marking" then I can delete most of the
hardcoded hacks. That'd be more than enough, and it's not that hard to implement.
*/

const double EPS = 1e-6;

bool equal(const double a, const double b) { return fabs(a - b) < EPS; }

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
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const double cross = (a - o).cross(b - o);

  if (equal(cross, 0)) return 0;
  return cross > 0 ? 1 : -1;
}

struct Segment {
  Point p, q;

  void intermediate_points(array<Point, 1000>& out, const int iterations = 20) const {
    int k = 0;
    const Point unit_dir = (q - p).normalize().rot_ccw();
    for (int i = 1; i < iterations; i++) {
      const double factor = (double)i / (double)iterations;
      const Point pt = scale(factor).q;
      out[k++] = pt + unit_dir.scale(1e-7);
    }
  }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    return intersect(s) ? make_pair(true, intersection_point(s))
                        : make_pair(false, Point{});
  }

  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  bool intersect(const Segment& s) const {
    const short o1 = orientation(p, q, s.p) * orientation(p, q, s.q) < 0;
    const short o2 = orientation(s.p, s.q, p) * orientation(s.p, s.q, q) < 0;
    return o1 && o2;
  }

 private:
  Point intersection_point(const Segment& s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

double tile_x, tile_y;

struct Tile {
  // TODO: Remove this struct
  Point p;

  array<Segment, 4> edges() const {
    const Point p1 = p;
    const Point p2 = p + Point{tile_x, 0};
    const Point p3 = p + Point{tile_x, tile_y};
    const Point p4 = p + Point{0, tile_y};
    return {Segment{p1, p2}, {p2, p3}, {p3, p4}, {p4, p1}};
  }

  static Tile at(const int i, const int j) {
    const Point p{i * tile_x, j * tile_y};
    return Tile{p};
  }
};

const int TILE_N = 11;

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
  const double factor = 20;

  auto add = [&](Point p) {
    if (p.x < 0 || p.y < 0) return;
    if (p.x > 6 * tile_x || p.y > 6 * tile_y) return;
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
          if (!intersect) continue;
          add(vertex + point - t);
        }
      }
    }

    for (int w = 0; w < (int)polygon.size(); w++) {
      const Point vert = polygon[w] - vertex;
      const Segment line{vert - unit_dir.scale(1e7), vert + unit_dir.scale(1e7)};

      for (int i = 0; i < TILE_N / 2; i++) {
        const auto [intersect1, point1] = line.intersect_non_collinear(
            {{i * tile_x, -1'000'000}, {i * tile_x, 1'000'000}});
        if (intersect1) add(vertex + point1 - vert);

        const auto [intersect2, point2] = line.intersect_non_collinear(
            {{-1'000'000, i * tile_y}, {1'000'000, i * tile_y}});
        if (intersect2) add(vertex + point2 - vert);
      }
    }
  }

  return offsets;
}

double angle(const Point& a, const Point& b) {
  const double x = atan2(a.cross(b), a * b);
  return x < 0 ? x + 2 * M_PI : x;
}

double angle(const Point& o, const Point& a, const Point& b) {
  return angle(a - o, b - o);
}

bool vertex_intersection(const vector<Point>& polygon, Segment s, const int i) {
  const Point v1 = polygon[i];
  if (orientation(s.p, s.q, v1) != 0 || (s.q - s.p) * (v1 - s.p) < 0) return false;

  const Point v0 = i == 0 ? polygon.back() : polygon[i - 1];
  const Point v2 = polygon[(i + 1) % polygon.size()];

  const double edges_ang = angle(v1, v0, v2);
  double p_ang = angle(v1, v0, s.p);
  double q_ang = angle(v1, v0, s.q);

  if (p_ang > q_ang) swap(p_ang, q_ang), swap(s.p, s.q);

  return orientation(v0, v1, s.p) == 0 ? q_ang < edges_ang : p_ang < edges_ang;
}

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  const Segment ray{p, {-10000, 10000}};

  int intersections = 0;

  for (int i = 0; i < (int)polygon.size(); i++) {
    const Segment edge{polygon[i], polygon[(i + 1) % polygon.size()]};
    intersections += edge.intersect(ray) || vertex_intersection(polygon, ray, i);
  }

  return intersections % 2 == 1;
}

array<Point, 1000> intermediate_points_return;

void mark_polygon_boundary(const vector<Point>& polygon) {
  for (int v = 0; v < (int)polygon.size(); v++) {
    const Segment edge{polygon[v], polygon[(v + 1) % polygon.size()]};

    for (int i = 0; i < TILE_N; i++) {
      for (int j = 0; j < TILE_N; j++) {
        if (tiles[i][j]) continue;
        const Tile t = Tile::at(i, j);

        for (const Segment& tile_edge : t.edges()) {
          if (tile_edge.intersect(edge)) {
            tiles[i][j] = true;
            break;
          }
        }
      }
    }

    const int inter = 11;
    edge.intermediate_points(intermediate_points_return, inter);

    for (int idx = 0; idx < inter - 1; idx++) {
      const Point p = intermediate_points_return[idx];
      const int i = p.x / tile_x;
      const int j = p.y / tile_y;
      tiles[i][j] = true;
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

    auto offsets = generate_offsets(polygon);

    for (const Point& offset : offsets) {
      vector<Point> shifted_polygon = polygon;
      for (Point& p : shifted_polygon) p = p + offset;

      memset(tiles, 0, sizeof tiles);

      mark_polygon_boundary(shifted_polygon);

      for (int i = 0; i < TILE_N; i++) {
        for (int j = 0; j < TILE_N; j++) {
          if (tiles[i][j]) continue;
          const Point p = Tile::at(i, j).p + Point{0.5, 0.5};
          tiles[i][j] = point_inside_polygon(p, shifted_polygon);
        }
      }

      ans = min(ans, tiles_count());
    }

    cout << ans << endl;
  }
}
