#include <bits/stdc++.h>
using namespace std;

// AC in Codeforces.
// TLE or WA in Beecrowd.
// Performance can be improved by merging clouds with the same direction.
// (i.e. set cloud1.wet[i][j] |= cloud2.wet[i][j])
// This leaves at most 4 clouds.
// Test data in Codeforces apparently used to be wrong (and may have already been fixed).

struct Point {
  int x, y;

  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  void operator+=(const Point& p) { *this = *this + p; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  Point operator*(const int f) const { return {x * f, y * f}; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point& p) const { return !(*this == p); }

  bool read_doubled() {
    if (cin >> x >> y) {
      x *= 2;
      y *= 2;
      return true;
    }
    return false;
  }

  Point unit_direction(const Point& p) const {
    if (x < p.x) return {1, 0};
    if (x > p.x) return {-1, 0};
    if (y < p.y) return {0, 1};
    return {0, -1};
  }

  bool out_bounds() const { return x < 0 || y < 0 || x > 200 || y > 200; }
};

struct Cloud {
  Point direction;

  bool is_wet(const Point& p, const int time) const {
    const Point q = p + (direction * -time);
    if (q.out_bounds()) return false;
    return wet[q.y][q.x];
  }

  void read_from_stdin() {
    int V;
    char dir;
    cin >> dir >> V;

    switch (dir) {
      case 'E':
        direction = {1, 0};
        break;
      case 'S':
        direction = {0, -1};
        break;
      case 'W':
        direction = {-1, 0};
        break;
      default:
        direction = {0, 1};
        break;
    }

    vertices = vector<Point>(V);

    for (Point& v : vertices) v.read_doubled();
    initialize();
  }

 private:
  bool wet[207][207];
  vector<Point> vertices;

  void iterate_polygon(const function<void(Point, Point)>& fn) const {
    for (int i = 0; i < (int)vertices.size(); i++) {
      Point curr = vertices[i];
      const Point next_point = vertices[(i + 1) % (int)vertices.size()];
      const Point dir = curr.unit_direction(next_point);

      for (;; curr += dir) {
        fn(curr, dir);
        if (curr == next_point) break;
      }
    }
  }

  void initialize() {
    memset(wet, 0, sizeof wet);

    iterate_polygon([&](const Point p, const Point _dir) { wet[p.y][p.x] = true; });

    iterate_polygon([&](Point curr, const Point& dir) {
      if (dir.y != 1) return;

      Point point_wet = curr;
      point_wet.x++;

      for (; !wet[point_wet.y][point_wet.x]; point_wet.x++) {
        wet[point_wet.y][point_wet.x] = true;
      }
    });

    iterate_polygon([&](const Point p, const Point _dir) { wet[p.y][p.x] = false; });
  }
};

Point src, dest;
bool visited[207][207][302];
const array<Point, 4> directions{Point{1, 0}, Point{-1, 0}, Point{0, 1}, Point{0, -1}};
vector<Cloud> clouds;

bool can_move(const Point& p, const Point& unit_direction, const int time) {
  for (const Cloud& c : clouds) {
    if (c.direction == unit_direction) {
      if (!c.is_wet(p, time * 2)) continue;
    }

    for (int i = 0; i <= 2; i++) {
      for (int j = 0; j <= 2; j++) {
        if (c.is_wet(p - (c.direction * i) + (unit_direction * j), time * 2))
          return false;
      }
    }
  }

  return true;
}

int solve() {
  memset(visited, 0, sizeof visited);

  int N;
  cin >> N;

  clouds.assign(N, Cloud());

  for (Cloud& c : clouds) c.read_from_stdin();

  queue<tuple<Point, int>> q;

  q.push({src, 0});
  visited[src.y][src.x][0] = true;

  while (!q.empty()) {
    auto [point, time] = q.front();
    q.pop();

    if (point == dest) return time;

    for (const Point& dir : directions) {
      const Point next_point = point + (dir * 2);
      if (next_point.out_bounds()) continue;
      if (visited[next_point.y][next_point.x][time + 1]) continue;

      if (can_move(point, dir, time)) {
        visited[next_point.y][next_point.x][time + 1] = true;
        q.push({next_point, time + 1});
      }
    }

    q.push({point, time + 1});
  }

  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (src.read_doubled() && dest.read_doubled()) {
    cout << solve() << endl;
  }
}
