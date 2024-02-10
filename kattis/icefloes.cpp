#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct DisjointSets {
  DisjointSets(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }

  int find(const int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rank[x] == rank[y]) rank[y]++;
  }

 private:
  vector<int> parent, rank;
};

struct Point {
  double x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  double operator*(const Point p) const { return x * p.x + y * p.y; }
  double dist2(const Point p) const {
    const Point v = (*this - p);
    return v * v;
  }
};

struct Segment {
  Point p, q;

  double dist2(const Segment s) const {
    assert(!intersect(s));
    return min({dist2(s.p), dist2(s.q), s.dist2(p), s.dist2(q)});
  }

  bool intersect(const Segment s) const {
    const bool o1 = orientation(p, q, s.p) != orientation(p, q, s.q);
    const bool o2 = orientation(s.p, s.q, p) != orientation(s.p, s.q, q);
    return o1 && o2;
  }

  double dist2(const Point r) const {
    if ((q - p) * (r - p) <= 0) return p.dist2(r);
    if ((p - q) * (r - q) <= 0) return q.dist2(r);
    return pow((q - p).cross(r - p), 2) / p.dist2(q);
  }

 private:
  int orientation(const Point p, const Point q, const Point r) const {
    const double val = (q - p).cross(r - p);
    if (fabs(val) < EPS) return 0;
    return val > 0 ? 1 : -1;
  }
};

stringstream read_line() {
  string line;
  getline(cin, line);
  replace(line.begin(), line.end(), '(', ' ');
  replace(line.begin(), line.end(), ')', ' ');
  return stringstream(line);
}

double polygon_area(const vector<Point>& polygon) {
  const int n = polygon.size();
  double total = 0;

  for (int i = n - 1, j = 0; j < n; i = j++) {
    total += polygon[i].cross(polygon[j]);
  }

  return fabs(total) / 2;
}

double polygon_dist2(const vector<Point>& vertices, const vector<Point>& edges) {
  const int n = edges.size();
  double res = DBL_MAX;

  for (int i = n - 1, j = 0; j < n; i = j++) {
    const Segment edge{edges[i], edges[j]};

    for (const Point p : vertices) {
      res = min(res, edge.dist2(p));
    }
  }

  return res;
}

bool distance_less_than(const vector<Point>& polygon1, const vector<Point>& polygon2,
                        const double d) {
  return polygon_dist2(polygon1, polygon2) <= d * d ||
         polygon_dist2(polygon2, polygon1) <= d * d;
}

bool point_inside_polygon(const Point p, const vector<Point>& polygon) {
  const Segment ray{p, {p.x + 1e7, p.y + 1e7 + 1e-2}};

  int intersections = 0;

  for (int i = 0; i < (int)polygon.size(); i++) {
    const Segment edge{polygon[i], polygon[(i + 1) % polygon.size()]};
    intersections += edge.intersect(ray);
  }

  return intersections % 2 == 1;
}

int find_polygon_container(const vector<vector<Point>>& polygons, const Point p) {
  for (int i = 0; i < (int)polygons.size(); i++) {
    if (point_inside_polygon(p, polygons[i])) return i;
  }

  return -1;
}

vector<Point> read_polygon() {
  stringstream ss = read_line();
  int n;
  ss >> n;
  vector<Point> res(n);
  for (auto& p : res) ss >> p.x >> p.y;
  return res;
}

optional<double> solve() {
  stringstream ss = read_line();
  int N;
  double d;
  ss >> N >> d;

  ss = read_line();
  Point A, B;
  ss >> A.x >> A.y;
  ss >> B.x >> B.y;

  vector<vector<Point>> floes;
  vector<double> areas;

  for (int i = 0; i < N; i++) floes.push_back(read_polygon());
  for (int i = 0; i < N; i++) areas.push_back(polygon_area(floes[i]));

  priority_queue<tuple<double, int, int>> edges;

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (distance_less_than(floes[i], floes[j], d)) {
        edges.emplace(min(areas[i], areas[j]), i, j);
      }
    }
  }

  const int s = find_polygon_container(floes, A);
  const int t = find_polygon_container(floes, B);

  if (s == -1 || t == -1) return nullopt;

  double ans = min(areas[s], areas[t]);

  DisjointSets ds(N);

  while (!edges.empty() && ds.find(s) != ds.find(t)) {
    const auto [w, u, v] = edges.top();
    edges.pop();

    ans = min(ans, w);
    ds.merge(u, v);
  }

  return ds.find(s) == ds.find(t) ? make_optional(ans) : nullopt;
}

int main() {
  int T;
  stringstream ss = read_line();
  ss >> T;
  while (T--) {
    const auto ans = solve();

    if (ans.has_value()) {
      cout << fixed << setprecision(9) << ans.value() << endl;
    } else {
      cout << "Scientists cannot meet" << endl;
    }
  }
}
