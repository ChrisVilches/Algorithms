#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  bool operator==(const Point p) const { return x == p.x && y == p.y; }
  bool operator<(const Point p) const { return x < p.x || (x == p.x && y > p.y); }
};

class Solution {
 public:
  int numberOfPairs(const vector<vector<int>>& points_list) {
    vector<Point> points;
    for (const auto& p : points_list) {
      points.push_back(Point{p.front(), p.back()});
    }

    int ans = 0;

    for (const Point pivot : points) {
      vector<Point> events;

      for (const Point q : points) {
        if (q.x < pivot.x) continue;
        if (q.y > pivot.y) continue;
        if (pivot == q) continue;

        events.emplace_back(q);
      }

      sort(events.begin(), events.end());
      set<int> present;

      for (const Point p : events) {
        const auto it = present.lower_bound(p.y);
        if (it == present.end()) ans++;
        present.emplace(p.y);
      }
    }

    return ans;
  }
};
