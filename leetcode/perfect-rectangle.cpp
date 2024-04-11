#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isRectangleCover(vector<vector<int>>& rectangles) {
    int min_x = INT_MAX;
    for (auto& rect : rectangles) min_x = min(min_x, rect[0]);
    for (auto& rect : rectangles) rect[0] -= min_x;
    for (auto& rect : rectangles) rect[2] -= min_x;

    map<int, int> curr;

    sort(rectangles.begin(), rectangles.end());

    for (const auto& rect : rectangles) {
      const int y1 = rect[1];
      const int y2 = rect[3];
      const int rect_width = rect[2] - rect[0];
      const int expected_width = rect[0];

      int width = 0;

      auto it = curr.lower_bound(y1);

      if (it != curr.end() && it->first == y1) {
        width = it->second;
      } else if (it != curr.begin()) {
        width = prev(it)->second;
      }

      if (width != expected_width) return false;

      while (it != curr.end()) {
        const auto next_it = next(it);
        const auto [it_y, it_width] = *it;

        if (y2 <= it_y) break;
        if (width != it_width) return false;

        curr.erase(it);
        it = next_it;
      }

      if (!curr.count(y2)) curr[y2] = width;
      curr[y1] = width + rect_width;
    }

    vector<pair<int, int>> ranges{curr.begin(), curr.end()};

    for (int i = 0; i < (int)ranges.size() - 2; i++) {
      const auto a = ranges[i].second;
      const auto b = ranges[i + 1].second;
      if (a != b) return false;
    }

    return true;
  }
};
