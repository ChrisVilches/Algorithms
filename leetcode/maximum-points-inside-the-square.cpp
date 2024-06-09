#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
    map<int, vector<char>> points_map;
    for (int i = 0; i < (int)points.size(); i++) {
      const int size = max(abs(points[i][0]), abs(points[i][1]));
      points_map[size].emplace_back(s[i]);
    }

    int ans = 0;

    set<char> curr;
    for (const auto& [_, tags] : points_map) {
      for (const char t : tags) {
        if (curr.count(t)) {
          return ans;
        }
        curr.emplace(t);
      }
      ans += tags.size();
    }

    return ans;
  }
};
