#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int dist(const Point p) const { return abs(x - p.x) + abs(y - p.y); }
};

class Solution {
  int point_edge(const Point p) const {
    if (p.y == 0) return 0;
    if (p.x == 0) return 3;
    if (p.y <= p.x) return 1;
    return 2;
  }

  bool possible(const vector<Point>& points, const int min_dist, const int k) {
    const int n = points.size();
    vector<int> link(n, -1);
    array<vector<Point>, 4> edges;

    for (int i = 0, j = 0; i < n; i++) {
      if (i >= j) j = i + 1;

      for (; j - i < n; j++) {
        if (points[i].dist(points[j % n]) >= min_dist) {
          link[i] = j;
          break;
        }
      }
    }

    for (int start_idx = 0; start_idx < n; start_idx++) {
      for (auto& e : edges) e.clear();

      for (int i = start_idx, rem = k; i - start_idx < n && i != -1; i = link[i % n]) {
        while (i < start_idx) i += n;

        const Point p = points[i % n];
        const int e = point_edge(p);
        auto& curr = edges[e];

        const auto& next = edges[(e + 1) % 4];

        if (!curr.empty() && curr.front().dist(p) < min_dist) break;
        if (!next.empty() && next.front().dist(p) < min_dist) break;

        curr.emplace_back(p);
        if (--rem == 0) return true;
      }
    }

    return false;
  }

 public:
  int maxDistance(const int side, const vector<vector<int>>& points_input, const int k) {
    vector<Point> points;
    for (const vector<int>& p : points_input) {
      points.emplace_back(p.front(), p.back());
    }

    sort(points.begin(), points.end(), [this](const Point p, const Point q) {
      const int s1 = point_edge(p);
      const int s2 = point_edge(q);
      if (s1 != s2) return s1 < s2;
      if (s1 == 0) return p.x < q.x;
      if (s1 == 1) return p.y < q.y;
      if (s1 == 2) return p.x > q.x;
      return p.y > q.y;
    });

    long long lo = 0;
    long long hi = side * 2;

    while (lo < hi) {
      const long long mid = (lo + hi) / 2;
      if (possible(points, mid, k)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return lo - 1;
  }
};
