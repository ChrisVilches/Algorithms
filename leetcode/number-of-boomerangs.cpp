#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int dist2(const Point p) const {
    const int dx = x - p.x;
    const int dy = y - p.y;
    return dx * dx + dy * dy;
  }
};

class Solution {
 public:
  int numberOfBoomerangs(const vector<vector<int>>& input) {
    vector<Point> points;
    for (const vector<int>& p : input) {
      points.emplace_back(p.front(), p.back());
    }

    int ans = 0;

    for (size_t i = 0; i < points.size(); i++) {
      unordered_map<int, int> freq;

      for (size_t j = 0; j < points.size(); j++) {
        if (i == j) continue;
        freq[points[i].dist2(points[j])]++;
      }

      for (const auto& [_, f] : freq) {
        ans += f * (f - 1);
      }
    }

    return ans;
  }
};
