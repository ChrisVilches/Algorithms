#include <bits/stdc++.h>
using namespace std;
using ld = long double;

struct DisjointSets {
  DisjointSets(int n) : parent(vector<int>(n)) { iota(parent.begin(), parent.end(), 0); }

  int find(int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) { parent[find(x)] = find(y); }

 private:
  vector<int> parent;
};

struct Point {
  ld x, y;
  ld dist(const Point p) const { return hypot(x - p.x, y - p.y); }
  ld operator*(const Point p) const { return x * p.x + y * p.y; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  ld cross(const Point p) const { return x * p.y - y * p.x; }
};

struct Segment {
  Point p, q;
  ld dist(const Point r) const {
    if ((q - p) * (r - p) <= 0) return p.dist(r);
    if ((p - q) * (r - q) <= 0) return q.dist(r);
    return fabs((q - p).cross(r - p)) / p.dist(q);
  }
};

struct Circle {
  Point center;
  ld r;
  bool intersects(const Circle& c) const { return center.dist(c.center) <= c.r + r; }
  bool intersects(const Segment& s) const { return s.dist(center) <= r; }
};

class Solution {
  bool should_merge(const Circle& c1, const Circle& c2, const ld x_corner,
                    const ld y_corner) const {
    if (!c1.intersects(c2)) return false;

    const ld d = c1.center.dist(c2.center);

    if (d <= abs(c1.r - c2.r)) return true;

    const ld a = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d);
    const ld h = sqrt(c1.r * c1.r - a * a);

    const Point q{c1.center.x + a * (c2.center.x - c1.center.x) / d,
                  c1.center.y + a * (c2.center.y - c1.center.y) / d};

    for (const int i : {-1, 1}) {
      const Point p = {q.x + i * h * (c2.center.y - c1.center.y) / d,
                       q.y - i * h * (c2.center.x - c1.center.x) / d};

      if (p.x >= 0 && p.x <= x_corner && p.y >= 0 && p.y <= y_corner) return true;
    }

    return false;
  }

 public:
  bool canReachCorner(int xCorner, int yCorner, vector<vector<int>>& circles) {
    const int n = circles.size();

    vector<Circle> cs;

    for (const vector<int>& c : circles) {
      cs.emplace_back(Circle{Point{(ld)c[0], (ld)c[1]}, (ld)c[2]});
    }

    DisjointSets ds(n);

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (should_merge(cs[i], cs[j], xCorner, yCorner)) {
          ds.merge(i, j);
        }
      }
    }

    const array<Point, 4> vertices{
        Point{0, 0},
        {(ld)xCorner, 0},
        {(ld)xCorner, (ld)yCorner},
        {0, (ld)yCorner},
    };

    vector<bitset<4>> intersections(n);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 4; j++) {
        const Segment s{vertices[j], vertices[(j + 1) % 4]};

        if (cs[i].intersects(s)) {
          intersections[ds.find(i)][j] = true;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      const auto& inter = intersections[ds.find(i)];
      const bool side1 = inter[0] || inter[1];
      const bool side2 = inter[2] || inter[3];
      if (side1 && side2) return false;
    }

    return true;
  }
};
