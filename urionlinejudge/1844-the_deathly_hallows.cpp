#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

double EPS = 1e-12;

struct Segment;

struct Point {
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  Point() {}
  Point operator+(const Point& p) { return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  inline double operator^(const Point& p) const {
    return (x * p.y) - (y * p.x);
  }
  Point scale(double f) { return Point(x * f, y * f); }
  Point to(const Point& p) const { return p - *this; }
  double operator*(const Point& p) { return x * p.x + y * p.y; }
  double dist(const Point& p) {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  }
  double dist(Segment& s);
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}

  double dist(Segment& s) {
    if (intersect(s)) return 0;
    return min({s.p.dist(*this), s.q.dist(*this), p.dist(s), q.dist(s)});
  }

  int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
  }

  bool intersect(const Segment& s) {
    Point p1 = p;
    Point q1 = q;
    Point p2 = s.p;
    Point q2 = s.q;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    return (o1 != o2 && o3 != o4);
  }
};

Point project_point_segment(Segment& s, Point c) {
  Point p = s.p;
  Point q = s.q;
  double r = p.to(q) * p.to(q);
  if (fabs(r) < EPS) return p;
  r = (p.to(c) * p.to(q)) / r;
  if (r < 0) return p;
  if (r > 1) return q;
  return p + p.to(q).scale(r);
}

double Point::dist(Segment& s) { return dist(project_point_segment(s, *this)); }

int N;

struct DisjointSets {
  vector<int> parent, rnk;

  DisjointSets(int n) {
    for (int i = 0; i <= n; i++) {
      rnk.push_back(0);
      parent.push_back(i);
    }
  }

  int find(int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rnk[x] > rnk[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rnk[x] == rnk[y]) rnk[y]++;
  }
};

struct Graph {
  int V;
  vector<pair<double, pii>> edges;

  Graph(int V) : V(V) {}

  void add_edge(int u, int v, double w) { edges.push_back({w, {u, v}}); }

  double kruskal_mst() {
    double mst_wt = 0;
    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector<pair<double, pii>>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++) {
      int u = it->second.first;
      int v = it->second.second;

      int set_u = ds.find(u);
      int set_v = ds.find(v);

      if (set_u != set_v) {
        mst_wt += it->first;
        ds.merge(set_u, set_v);
      }
    }

    return mst_wt;
  }
};

int round_up(double n) { return fabs(floor(n) - n) < EPS ? floor(n) : ceil(n); }

void solve() {
  vector<Segment> segments;

  for (int i = 0; i < N; i++) {
    Segment s;
    scanf("%lf %lf %lf %lf", &s.p.x, &s.p.y, &s.q.x, &s.q.y);
    segments.push_back(s);
  }

  Graph g(segments.size());

  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      g.add_edge(i, j, segments[i].dist(segments[j]));

  printf("%d\n", round_up(g.kruskal_mst()));
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
