#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  bool operator!=(const Point p) const { return x != p.x || y != p.y; }
  bool operator<(const Point p) const { return y > p.y || (y == p.y && x > p.x); }
};

class Solution {
 public:
  int numberOfPairs(const vector<vector<int>>& points_list) {
    vector<Point> points;

    for (const auto& p : points_list) {
      points.push_back(Point{p.front(), p.back()});
    }

    int ans = 0;

    sort(points.begin(), points.end());

    for (const Point pivot : points) {
      vector<Point> other;
      copy_if(points.begin(), points.end(), back_inserter(other), [&](const Point p) {
        return pivot != p && p.x >= pivot.x && p.y <= pivot.y;
      });

      Point last;

      for (size_t i = 0; i < other.size(); i++) {
        const Point p = other[i];

        if (i == 0) {
          last = p;
          ans++;
        } else if (last.y == p.y) {
          last = p;
        } else if (p.x < last.x) {
          last = p;
          ans++;
        }
      }
    }

    return ans;
  }
};
